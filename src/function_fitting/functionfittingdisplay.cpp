#include "functionfittingdisplay.h"

FunctionFittingDisplay::FunctionFittingDisplay(QWidget *parent) :
  QChartView(parent), myscene(nullptr)
{}

void FunctionFittingDisplay::setScene(QChart *scene)
{
  this->setChart(scene);
  myscene = dynamic_cast<FunctionFitting *>(scene);
}
