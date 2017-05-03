#ifndef MEMORYALLOCATIONDISPLAY_H
#define MEMORYALLOCATIONDISPLAY_H

#include <QGraphicsView>
#include <QResizeEvent>

#include "memory_allocation/memory_allocation.h"

class MemoryAllocationDisplay : public QGraphicsView
{
    Q_OBJECT

    MemoryAllocation * myscene;

  public:
    MemoryAllocationDisplay(QWidget * parent = 0);
    void setScene(QGraphicsScene * scene);
    void resizeEvent(QResizeEvent *event);

  public slots:
    void setGlobalView();
    void setCPUUsedByRAM();
    void setRAMUsedByCPU();
    void setRAM(int);
    void setCore(int);
};

#endif // MEMORYALLOCATIONDISPLAY_H
