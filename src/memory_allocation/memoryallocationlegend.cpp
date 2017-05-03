#include "memoryallocationlegend.h"
#include "ui_memoryallocationlegend.h"

MemoryAllocationLegend::MemoryAllocationLegend(QWidget *parent) :
  QWidget(parent, Qt::Window),
  ui(new Ui::MemoryAllocationLegend)
{
  ui->setupUi(this);
}

MemoryAllocationLegend::~MemoryAllocationLegend()
{
  delete ui;
}
