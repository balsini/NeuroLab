#ifndef GAERRORPLOT_H
#define GAERRORPLOT_H

#include <vector>

#include <QChart>
#include <QChartView>
#include <QLineSeries>

QT_CHARTS_USE_NAMESPACE

class GAErrorPlot : public QChartView
{
    Q_OBJECT

    QChart *chart;

    unsigned int _epoch;
    QLineSeries _cost;

  public:
    GAErrorPlot(QWidget *parent = Q_NULLPTR);
    ~GAErrorPlot() { delete chart; }
    void addEpochMinValue(double v);
    void plot();
    void clear() {
      _epoch = 0;
      _cost.clear();
    }
};

#endif // GAERRORPLOT_H
