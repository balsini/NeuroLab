#include "buttonlegend.h"

ButtonLegend::ButtonLegend(QWidget *parent) : QPushButton(parent)
{}

void ButtonLegend::showNumericalValue(int v)
{
  this->setText(QString::number(v));
}
