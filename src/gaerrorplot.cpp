#include "gaerrorplot.h"

#include <QBarCategoryAxis>
#include <QValueAxis>

GAErrorPlot::GAErrorPlot(QWidget *parent)
  : QChartView(parent)
{
  _epoch = 0;

  chart = new QChart();

  //chart->setTitle("Cost");
  chart->setAnimationOptions(QChart::SeriesAnimations);

  chart->legend()->setVisible(false);
  //chart->legend()->setAlignment(Qt::AlignBottom);

  setRenderHint(QPainter::Antialiasing);

  this->setChart(chart);

}


void GAErrorPlot::addEpochMinValue(double v)
{
  _cost.append(_epoch++, v);
}

void GAErrorPlot::plot()
{
  int max, min;

  chart->addSeries(&_cost);

  //QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(chart->axes(Qt::Horizontal).at(0));
  //axisX->setCategories(categories);
  //axisX->setMax(1000);

  max = min = _cost.at(0).y();
  for (int i = 1; i<_cost.count(); ++i) {
    if (_cost.at(i).y() > max)
      max = _cost.at(i).y();
    if (_cost.at(i).y() < min)
      min = _cost.at(i).y();

  }

  chart->createDefaultAxes();

  QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
  axisY->setMax(max);
  axisY->setMin(min);

  QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).at(0));
  axisX->setMax(_cost.count());
  axisX->setMin(0);
}
