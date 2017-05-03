#include "memoryallocationdisplay.h"

#include <QDebug>

MemoryAllocationDisplay::MemoryAllocationDisplay(QWidget * parent) :
  QGraphicsView(parent)
{
  myscene = nullptr;

  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void MemoryAllocationDisplay::resizeEvent(QResizeEvent * event)
{
  if (myscene != nullptr)
    myscene->refreshView();
}

void MemoryAllocationDisplay::setScene(QGraphicsScene * scene)
{
  QGraphicsView::setScene(scene);
  myscene = dynamic_cast<MemoryAllocation *>(scene);
  connect(myscene, SIGNAL(RAM_counted(int,int,int,int,int)),
          this, SLOT(RAM_occupations(int,int,int,int,int)));
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
