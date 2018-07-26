#include "functionfitting.h"

#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QGraphicsView>

#include <cassert>
#include <algorithm>
#include <cmath>
#include <random>

#include "error_function.h"


FunctionFitting::FunctionFitting(QGraphicsItem *parent) :
  QChart(parent)
{
  for (unsigned int i=0; i<function.dataSize(); ++i)
    reference_series.append(function.x(i), function.y(i));

  /*
  for (int i=-100; i<=100; i+=30)
    reference_series.append(i, i*i*i);
  */
  //chart->setTitle("Cost");
  //chart->setAnimationOptions(QChart::SeriesAnimations);

  legend()->setVisible(false);
  //legend()->setAlignment(Qt::AlignBottom);
  //setRenderHint(QPainter::Antialiasing);

  //this->setChart(chart->chart());

  setTitle("Fitness function");

  addSeries(&reference_series);
  addSeries(&ga_series);

  ga_series.setMarkerShape(QScatterSeries::MarkerShapeRectangle);

  reference_series.setMarkerSize(10);
  ga_series.setMarkerSize(reference_series.markerSize() / 1.5);

  QColor border = QColor::fromRgb(0, 0, 0);
  reference_series.setBorderColor(border);
  ga_series.setBorderColor(border);

  createDefaultAxes();
}


unsigned int FunctionFitting::getSolutionSize() const
{
  return function.variables();
}


long double FunctionFitting::evaluateSolution(const std::vector<long double> &s) const
{
  std::vector<std::pair<long double, long double> > errors;

  for (unsigned int i=0; i<function.dataSize(); ++i) {
    double y = function.y(i);
    double yt = function.evaluate(function.x(i), s);

    errors.push_back(std::make_pair(y, yt));
  }

  return error_max_relative(errors);
}


void FunctionFitting::showSolution(const std::vector<long double> &s)
{
  /*
  int x, y;
  std::vector<Coordinate> steps;

  for (int p : s) {
    x = targets[p]->x();
    y = targets[p]->y();

    steps.push_back(std::make_pair(x, y));
  }
  setPath(steps);
  */

  ga_series.clear();
  for (unsigned int i=0; i<function.dataSize(); ++i) {
    auto x = function.x(i);
    auto y = function.evaluate(x, s);
    ga_series.append(x, y);
  }

  QString data;
  for (unsigned int i=0; i<s.size(); ++i) {
    double n = s.at(i);
    data.append(QString::number(n) + ", ");
  }

  qDebug() << "Error: " << QString::number(static_cast<double>(evaluateSolution(s)))
           << "\tSolution:" << data;
}


std::vector<long double> FunctionFitting::crossover(const std::vector<long double> &a,
                                                    const std::vector<long double> &b)
{
  std::vector<long double> ret;
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine g(seed);
  std::uniform_int_distribution<int> d(0, 1);

  for (unsigned int i=0; i<a.size(); ++i)
    ret.push_back(d(g) == 0 ? a[i] : b[i]);

  return ret;
}


void FunctionFitting::mutate(std::vector<long double> &c)
{
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine g(seed);
  std::uniform_int_distribution<unsigned int> index(0, c.size() - 1);
  double newValue;
  unsigned int i=index(g);

  //for (unsigned int i=0; i<c.size(); ++i) {
    do {
      std::uniform_real_distribution<long double> s(-1.1, 1.1);
      newValue = c[i] + c[i] * s(g);
    } while (newValue < function.getConstraints().at(i).first || newValue > function.getConstraints().at(i).second);
    c[i] = newValue;
  //}
}


std::vector<long double> FunctionFitting::getRandomSolution() const
{
  std::vector<long double> s;
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine g(seed);

  for (unsigned int i=0; i<function.variables(); ++i){
    std::uniform_real_distribution<long double> d(function.getConstraints().at(i).first,
                                                  function.getConstraints().at(i).second);
    s.push_back(d(g));
  }

  return s;
}
