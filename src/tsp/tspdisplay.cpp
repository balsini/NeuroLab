#include "tspdisplay.h"

TSPDisplay::TSPDisplay(QWidget * parent) :
  QGraphicsView(parent)
{}

void TSPDisplay::setScene(QGraphicsScene * scene)
{
  QGraphicsView::setScene(scene);
  myscene = dynamic_cast<TSP *>(scene);
}
