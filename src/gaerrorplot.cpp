#include "gaerrorplot.h"

#include <QBarCategoryAxis>
#include <QValueAxis>

GAErrorPlot::GAErrorPlot(QWidget *parent)
  : QChartView(parent)
{
  _epoch = 0;

  chart = new QChart();

  //chart->setTitle("Cost");
  //chart->setAnimationOptions(QChart::SeriesAnimations);

  chart->legend()->setVisible(false);
  //chart->legend()->setAlignment(Qt::AlignBottom);

  //setRenderHint(QPainter::Antialiasing);

  this->setChart(chart);

  chart->addSeries(&_cost);
  chart->addSeries(&_mean);
}


void GAErrorPlot::addEpochValues(double min, double mean)
{
  _cost.append(_epoch, min);
  _mean.append(_epoch, mean);
  _epoch++;
}


void GAErrorPlot::plot()
{
  qreal max, min;

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
