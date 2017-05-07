#ifndef MEMORYALLOCATIONDISPLAY_H
#define MEMORYALLOCATIONDISPLAY_H

#include <cstdint>

#include <QGraphicsView>
#include <QResizeEvent>

#include "memory_allocation.h"

class MemoryAllocationDisplay : public QGraphicsView
{
    Q_OBJECT

    MemoryAllocation *myscene;

  public:
    MemoryAllocationDisplay(QWidget * parent = 0);
    void setScene(QGraphicsScene * scene);
    void resizeEvent(QResizeEvent *event);

  public slots:
    void setRAM(uint8_t);
    void setCore(uint8_t);

  public slots:
    void RAM_occupations(int LRAM0, int LRAM1, int LRAM2, int LRAM3, int GRAM);

  signals:
    void LRAM_0_counted(int);
    void LRAM_1_counted(int);
    void LRAM_2_counted(int);
    void LRAM_3_counted(int);
    void GRAM_counted(int);
};

#endif // MEMORYALLOCATIONDISPLAY_H
