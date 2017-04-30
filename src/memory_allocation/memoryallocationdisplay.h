#ifndef MEMORYALLOCATIONDISPLAY_H
#define MEMORYALLOCATIONDISPLAY_H

#include <QGraphicsView>
#include <QResizeEvent>

#include "memory_allocation/memory_allocation.h"

class MemoryAllocationDisplay : public QGraphicsView
{
    MemoryAllocation * myscene;
  public:
    MemoryAllocationDisplay(QWidget * parent = 0);
    void setScene(QGraphicsScene * scene);
    void resizeEvent(QResizeEvent * event);
};

#endif // MEMORYALLOCATIONDISPLAY_H
