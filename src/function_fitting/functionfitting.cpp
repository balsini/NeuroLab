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

  for (int i=-100; i<=100; i+=30)
    reference_series.append(i, i*i*i);

  //chart->setTitle("Cost");
  //chart->setAnimationOptions(QChart::SeriesAnimations);

  //chart->legend()->setVisible(false);
  legend()->setAlignment(Qt::AlignBottom);
  //setRenderHint(QPainter::Antialiasing);

  //this->setChart(chart->chart());

  setTitle("Fitness function");

  addSeries(&reference_series);
  addSeries(&ga_series);
  createDefaultAxes();
}

unsigned int FunctionFitting::getSolutionSize() const
{
  return variables;
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
  /*
  for (unsigned int i=0; i<s.size(); ++i) {
    int x1, x2, y1, y2;

    x1 = targets[s[i]]->x();
    x2 = targets[s[(i + 1) % s.size()]]->x();

    y1 = targets[s[i]]->y();
    y2 = targets[s[(i + 1) % s.size()]]->y();

    _cost += sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  }
  */
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
  for (int i=-100; i<=100; i+=30)
    ga_series.append(i, i*i);
}

std::vector<long double> FunctionFitting::crossover(const std::vector<long double> &a, const std::vector<long double> &b)
{
  std::vector<long double> ret;
  /*
  std::vector<long double> sub_sol;
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> d1(0, a.size() - 2);
  unsigned int c1, c2;
  unsigned int i;

  c1 = d1(generator);

  std::uniform_int_distribution<int> d2(c1 + 1, targets.size() - 1);

  c2 = d2(generator);

  for (i=c1; i<c2; ++i)
    sub_sol.push_back(a[i]);

  i = 0;
  while (ret.size() < c1) {
    if (std::find(sub_sol.begin(), sub_sol.end(), b[i]) == sub_sol.end())
      ret.push_back(b[i]);
    ++i;
  }

  for (auto v : sub_sol)
    ret.push_back(v);

  while (ret.size() < a.size()) {
    if (std::find(sub_sol.begin(), sub_sol.end(), b[i]) == sub_sol.end())
      ret.push_back(b[i]);
    ++i;
  }
  */
  return ret;
}

void FunctionFitting::mutate(std::vector<long double> &c)
{
  /*
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> d(0, c.size() - 1);

  std::swap(c[d(generator)], c[d(generator)]);
  */
}

std::vector<long double> FunctionFitting::getRandomSolution() const
{
  std::vector<long double> s;
  /*
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_real_distribution<long double> distribution(0, targets.size() - 1);


  for (unsigned int i=0; i<targets.size(); ++i)
    s.push_back(i);

  for (unsigned int i=0; i<s.size(); ++i)
    std::swap(s[i], s[distribution(generator)]);
  */
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
