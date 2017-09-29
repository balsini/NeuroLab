#include "functionfittingdisplay.h"

FunctionFittingDisplay::FunctionFittingDisplay(QWidget * parent) :
  QChartView(parent)
{}

void FunctionFittingDisplay::setScene(QChart * scene)
{
  QChartView::setChart(scene);
  myscene = dynamic_cast<FunctionFitting *>(scene);
}

void FunctionFittingDisplay::resizeEvent(QResizeEvent * event)
{
  if (myscene != nullptr)
    myscene->refreshView();
}
