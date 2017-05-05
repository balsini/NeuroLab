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
    QLineSeries _mean;

    double _max;
    double _min;

  public:
    GAErrorPlot(QWidget *parent = Q_NULLPTR);
    ~GAErrorPlot() { delete chart; }
    void addEpochValues(double min, double mean);
    void plot();
    void clear();
};

#endif // GAERRORPLOT_H
