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

void MemoryAllocationDisplay::setRAM(uint8_t r)
{
  myscene->setRAM(r);
}

void MemoryAllocationDisplay::setCore(uint8_t c)
{
  myscene->setCore(c);
}

void MemoryAllocationDisplay::RAM_occupations(int a, int b, int c, int d, int e)
{
  emit LRAM_0_counted(a);
  emit LRAM_1_counted(b);
  emit LRAM_2_counted(c);
  emit LRAM_3_counted(d);
  emit GRAM_counted(e);
}
