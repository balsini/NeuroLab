#include "tsp.h"

#include <QGraphicsSceneMouseEvent>

const unsigned int radius = 5;

TSP::TSP(QObject * parent) :
  QGraphicsScene(parent)
{
}


void TSP::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
  addEllipse(mouseEvent->scenePos().x(),
             mouseEvent->scenePos().y(),
             radius,
             radius);
}
