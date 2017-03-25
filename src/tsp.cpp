#include "tsp.h"

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <algorithm>
#include <cmath>

const int radius = 8;
QBrush brush;

TSP::TSP(QObject *parent) :
  QGraphicsScene(parent)
{
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::red);
}


void TSP::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
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
  for (auto i : steps)
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
