#include "tsp.h"

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

TSP::TSP(QObject *parent) :
  QGraphicsScene(parent)
{
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::red);
}

unsigned int TSP::getSolutionSize() const
{
  return targets.size();
}

void TSP::addProblemElement(int x, int y)
{
  QGraphicsItem *to_add;

  to_add = addEllipse(0,0,
                      radius, radius, QPen(), brush);
  to_add->setPos(x, y);

  targets.push_back(to_add);
}

void TSP::removeProblemElement(int x, int y)
{
  QGraphicsItem *to_delete;

  to_delete = itemAt(x, y, QTransform());
  if (to_delete) {
    auto i = find(targets.begin(), targets.end(), to_delete);
    if (i != targets.end()) {
      targets.erase(i);
      removeItem(to_delete);
    }
  }
}

void TSP::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  switch (mouseEvent->button()) {
  case Qt::LeftButton:
    addProblemElement(mouseEvent->scenePos().x(), mouseEvent->scenePos().y());
    break;
  case Qt::RightButton:
    removeProblemElement(mouseEvent->scenePos().x(),
                         mouseEvent->scenePos().y());
    break;
  default: break;
  }
}

std::vector<Coordinate> TSP::getTargets()
{
  std::vector<Coordinate> ret;

  for (QGraphicsItem *p : targets)
    ret.push_back(std::make_pair(p->x(),
                                 p->y()));

  return ret;
}

void TSP::setPath(const std::vector<Coordinate> &s)
{
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
}

double TSP::evaluateSolution(const std::vector<int> &s) const
{
  double _cost = 0;

  for (unsigned int i=0; i<s.size(); ++i) {
    int x1, x2, y1, y2;

    x1 = targets[s[i]]->x();
    x2 = targets[s[(i + 1) % s.size()]]->x();

    y1 = targets[s[i]]->y();
    y2 = targets[s[(i + 1) % s.size()]]->y();

    _cost += sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
  }

  return _cost;
}

void TSP::showSolution(const std::vector<int> &s)
{
  int x, y;
  std::vector<Coordinate> steps;

  for (int p : s) {
    x = targets[p]->x();
    y = targets[p]->y();

    steps.push_back(std::make_pair(x, y));
  }
  setPath(steps);
}

std::vector<int> TSP::crossover(const std::vector<int> &a, const std::vector<int> &b)
{
  std::vector<int> ret;
  std::vector<int> sub_sol;
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

  return ret;
}

void TSP::mutate(std::vector<int> &c)
{
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> d(0, c.size() - 1);

  std::swap(c[d(generator)], c[d(generator)]);
}

std::vector<int> TSP::getRandomSolution() const
{
  static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  static std::default_random_engine generator(seed);
  std::uniform_int_distribution<int> distribution(0, targets.size() - 1);

  std::vector<int> s;

  for (unsigned int i=0; i<targets.size(); ++i)
    s.push_back(i);

  for (unsigned int i=0; i<s.size(); ++i)
    std::swap(s[i], s[distribution(generator)]);

  return s;
}

void TSP::generateRandom(unsigned int size)
{
  qDebug() << "TODO generateRandom" << size;

  QGraphicsView *view = this->views().first();

  int w = view->width() - 10;
  int h = view->height() - 10;

  std::random_device r;
  std::mt19937 e(r());
  std::uniform_int_distribution<int> w_dist(0, w);
  std::uniform_int_distribution<int> h_dist(0, h);

  for (unsigned int i=0; i<size; ++i) {


    addProblemElement(w_dist(e), h_dist(e));
  }
}

void TSP::clear()
{
  targets.clear();
  steps.clear();
  QGraphicsScene::clear();
}
