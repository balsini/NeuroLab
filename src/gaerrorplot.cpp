#include "gaerrorplot.h"

#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QLegend>

GAErrorPlot::GAErrorPlot(QWidget *parent)
  : QChartView(parent)
{
  _epoch = 0;

  chart = new QChart;

  //chart->setTitle("Cost");
  //chart->setAnimationOptions(QChart::SeriesAnimations);

  //chart->legend()->setVisible(false);
  chart->legend()->setAlignment(Qt::AlignBottom);
  //setRenderHint(QPainter::Antialiasing);

  this->setChart(chart);

  chart->setTitle("Fitness function");

  _cost.setName("Best in population");
  _mean.setName("Mean population value");
  chart->addSeries(&_cost);
  chart->addSeries(&_mean);
}


GAErrorPlot::~GAErrorPlot()
{
  delete chart;
}


void GAErrorPlot::addEpochValues(double min, double mean)
{
  if (_cost.count() == 0) {
    _max = min;
    _min = min;
  } else {
    if (_max < min)
      _max = min;
    if (_min > min)
      _min = min;
  }

  _cost.append(_epoch, min);
  _mean.append(_epoch, mean);

  _epoch++;
}


void GAErrorPlot::plot()
{
  chart->createDefaultAxes();

  QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).at(0));
  axisY->setMax(_max);
  axisY->setMin(_min);

  QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).at(0));
  axisX->setMax(_cost.count());
  axisX->setMin(0);
}


void GAErrorPlot::clear()
{
  _epoch = 0;
  _cost.clear();
  _mean.clear();
}
