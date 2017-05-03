#ifndef MEMORYALLOCATIONLEGEND_H
#define MEMORYALLOCATIONLEGEND_H

#include <QWidget>

namespace Ui {
  class MemoryAllocationLegend;
}

class MemoryAllocationLegend : public QWidget
{
    Q_OBJECT

  public:
    explicit MemoryAllocationLegend(QWidget *parent = 0);
    ~MemoryAllocationLegend();

  private:
    Ui::MemoryAllocationLegend *ui;
};

#endif // MEMORYALLOCATIONLEGEND_H
