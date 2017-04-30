#include "memoryallocationdisplay.h"

MemoryAllocationDisplay::MemoryAllocationDisplay(QWidget * parent) :
  QGraphicsView(parent)
{
  myscene = nullptr;
  this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
  this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
}

void MemoryAllocationDisplay::resizeEvent(QResizeEvent * event)
{
  if (myscene != nullptr)
    myscene->resizeEvent(event);
}

void MemoryAllocationDisplay::setScene(QGraphicsScene * scene)
{
  QGraphicsView::setScene(scene);
  myscene = dynamic_cast<MemoryAllocation *>(scene);
}
