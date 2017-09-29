#include "functionfittingdisplay.h"

FunctionFittingDisplay::FunctionFittingDisplay(QWidget *parent) :
  QChartView(parent)
{}

void FunctionFittingDisplay::setScene(QChart *scene)
{
  this->setChart(scene);
  myscene = dynamic_cast<FunctionFitting *>(scene);
}

void FunctionFittingDisplay::resizeEvent(QResizeEvent *event)
{
  if (myscene != nullptr)
    myscene->refreshView();
}

void FunctionFittingDisplay::clear()
{
  myscene->clear();
}
