#include "functionfitting.h"

#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QGraphicsView>

#include <algorithm>
#include <cmath>
#include <random>

static const int radius = 8;
static QBrush brush;

FunctionFitting::FunctionFitting(QGraphicsItem *parent) :
  QChart(parent)
{
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::red);

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
  createDefaultAxes();
}

unsigned int FunctionFitting::getSolutionSize() const
{
  return function.variables();
}

void FunctionFitting::addProblemElement(int x, int y)
{
  /*
  QGraphicsItem *to_add;

  to_add = addEllipse(0,0,
                      radius, radius, QPen(), brush);
  to_add->setPos(x, y);

  targets.push_back(to_add);
  */
}

void FunctionFitting::removeProblemElement(int x, int y)
{
  /*
  QGraphicsItem *to_delete;

  to_delete = itemAt(x, y, QTransform());
  if (to_delete) {
    auto i = find(targets.begin(), targets.end(), to_delete);
    if (i != targets.end()) {
      targets.erase(i);
      removeItem(to_delete);
    }
  }
  */
}

std::vector<Coordinate> FunctionFitting::getTargets()
{
  std::vector<Coordinate> ret;
  /*
  for (QGraphicsItem *p : targets)
    ret.push_back(std::make_pair(p->x(),
                                 p->y()));
*/
  return ret;
}

void FunctionFitting::setPath(const std::vector<Coordinate> &s)
{
  /*
  for (auto &i : steps)
    removeItem(i);
  steps.clear();

  for (unsigned int i=0; i<s.size(); ++i) {
    const Coordinate &c1 = s[i];
    const Coordinate &c2 = s[(i + 1) % s.size()];

    steps.push_back(addLine(c1.first + radius / 2, c1.second + radius / 2,
                            c2.first + radius / 2, c2.second + radius / 2,
                            QPen()));
  }
  */
}

double FunctionFitting::evaluateSolution(const std::vector<long double> &s) const
{
  double _cost = 0;

  for (unsigned int i=0; i<function.dataSize(); ++i) {
    double y = function.y(i);
    double yt = function.evaluate(function.x(i), s);

    _cost += sqrt((y - yt) * (y - yt));
  }

  return _cost;
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
  for (int i=0; i<function.dataSize(); ++i) {
    auto x = function.x(i);
    auto y = function.evaluate(x, s);
    ga_series.append(x, y);
  }

  QString data;
  for (unsigned int i=0; i<s.size(); ++i) {
    double n = s.at(i);
    data.append(QString::number(n) + " ");
  }

  qDebug() << "Solution:" << data;
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
  double newValue;

  for (unsigned int i=0; i<c.size(); ++i) {
    do {
      std::uniform_real_distribution<long double> s(-1.1, 1.1);
      newValue = c[i] + c[i] * s(g);
    } while (newValue < function.getConstraints().at(i).first || newValue > function.getConstraints().at(i).second);
    c[i] = newValue;
  }
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


void FunctionFitting::clear()
{
  /*
  targets.clear();
  steps.clear();

  QGraphicsScene::clear();
  */
}

void FunctionFitting::refreshView()
{
  qDebug() << "Resized";
  //adjustSize();
  //update();
}
