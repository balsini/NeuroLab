#ifndef FUNCTIONFITTING_H
#define FUNCTIONFITTING_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QScatterSeries>
#include <QLineSeries>
#include <QChartView>

#include <chrono>
#include <vector>

#include "optimizationproblem.h"

using namespace QtCharts;

typedef std::pair<int, int> Coordinate;

class FunctionFitting : public QChart, public GAOptimizationProblem<long double>
{
    Q_OBJECT

    QScatterSeries reference_series;
    QLineSeries ga_series;
    unsigned int variables;

  public:
    FunctionFitting(QGraphicsItem *parent = Q_NULLPTR);
    std::vector<Coordinate> getTargets();
    void setPath(const std::vector<Coordinate> &steps);
    unsigned int getSolutionSize() const;
    double evaluateSolution(const std::vector<long double> &s) const;
    void showSolution(const std::vector<long double> &s);
    std::vector<long double> crossover(const std::vector<long double> &a, const std::vector<long double> &b);
    void mutate(std::vector<long double> &);
    std::vector<long double> getRandomSolution() const;
    void addProblemElement(int x, int y);
    void removeProblemElement(int x, int y);
    void refreshView();
    void clear();
};

#endif // FUNCTIONFITTING_H
