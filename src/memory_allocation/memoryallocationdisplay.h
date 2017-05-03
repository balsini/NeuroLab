#ifndef MEMORYALLOCATIONDISPLAY_H
#define MEMORYALLOCATIONDISPLAY_H

#include <QGraphicsView>
#include <QResizeEvent>

#include "memory_allocation.h"
#include "memoryallocationlegend.h"

class MemoryAllocationDisplay : public QGraphicsView
{
    Q_OBJECT

    MemoryAllocation *myscene;
    MemoryAllocationLegend *legend;

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
    void showLegend();
};

#endif // MEMORYALLOCATIONDISPLAY_H
