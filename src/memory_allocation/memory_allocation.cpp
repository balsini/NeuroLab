#include "memory_allocation.h"

#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <algorithm>
#include <cmath>

static const int radius = 8;
static QBrush brush;

MemoryAllocation::MemoryAllocation(QObject *parent) :
  QGraphicsScene(parent)
{
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::red);
}

void MemoryAllocation::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  switch (mouseEvent->button()) {
    case Qt::LeftButton:
      QGraphicsItem *to_add;

      to_add = addEllipse(0,0,
                          radius, radius, QPen(), brush);
      to_add->setPos(mouseEvent->scenePos().x(),
                     mouseEvent->scenePos().y());

      targets.push_back(to_add);
      break;
    case Qt::RightButton:
      QGraphicsItem *to_delete;

      to_delete = itemAt(mouseEvent->scenePos().x(),
                         mouseEvent->scenePos().y(),
                         QTransform());
      if (to_delete) {
        auto i = find(targets.begin(), targets.end(), to_delete);
        if (i != targets.end()) {
          targets.erase(i);
          removeItem(to_delete);
        }
      }
      break;
    default: break;
  }
}

std::vector<Coordinate> MemoryAllocation::getTargets()
{
  std::vector<Coordinate> ret;

  for (QGraphicsItem *p : targets)
    ret.push_back(std::make_pair(p->x(),
                                 p->y()));

  return ret;
}

double MemoryAllocation::evaluateSolution(const std::vector<int> &s) const
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

void MemoryAllocation::showSolution(const std::vector<int> &s)
{


}

std::vector<int> MemoryAllocation::crossover(const std::vector<int> &a, const std::vector<int> &b)
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

std::vector<int> MemoryAllocation::getRandomSolution() const
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

void MemoryAllocation::resizeEvent(QResizeEvent *event)
{
  qDebug() << "sceneRectChanged(const QRectF &rect)" << event->size();

  qreal rect_width = event->size().width() / 100.0;
  qreal rect_height = event->size().height() / 100.0;

  QGraphicsItem *to_add;

  this->clear();

  for (unsigned int i=0; i<100; ++i) {
    for (unsigned int j=0; j<100; ++j) {
      to_add = addRect(0, 0, rect_width, rect_height);

      to_add->setPos(j * rect_width, i * rect_height);
    }
  }
}
