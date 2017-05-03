#include "memoryallocationdisplay.h"

#include <QDebug>

MemoryAllocationDisplay::MemoryAllocationDisplay(QWidget * parent) :
  QGraphicsView(parent)
{
  myscene = nullptr;

  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  legend = new MemoryAllocationLegend(this);
}

void MemoryAllocationDisplay::resizeEvent(QResizeEvent * event)
{
  if (myscene != nullptr)
    myscene->resizeEvent(width(), height());
}

void MemoryAllocationDisplay::setScene(QGraphicsScene * scene)
{
  QGraphicsView::setScene(scene);
  myscene = dynamic_cast<MemoryAllocation *>(scene);
}

void MemoryAllocationDisplay::setGlobalView()
{
  myscene->setView(GLOBAL_RAM_VIEW);
}

void MemoryAllocationDisplay::setRAMUsedByCPU()
{
  myscene->setView(RAM_USED_BY_CPU_VIEW);
}

void MemoryAllocationDisplay::setRAM(uint8_t r)
{
  myscene->setRAM(r);
}

void MemoryAllocationDisplay::setCore(int c)
{
  myscene->setCore(c);
}

void MemoryAllocationDisplay::showLegend()
{
  legend->setVisible(true);
}
