#ifndef FUNCTIONFITTING_H
#define FUNCTIONFITTING_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QScatterSeries>
#include <QChartView>

#include <chrono>
#include <vector>

#include "optimizationproblem.h"
#include "function_fitting/advanced_0/function.h"

using namespace QtCharts;

class FunctionFitting : public QChart, public GAOptimizationProblem<long double>
{
    Q_OBJECT

    FunctionToFit function;
    QScatterSeries reference_series;
    QScatterSeries ga_series;

  public:
    FunctionFitting(QGraphicsItem *parent = Q_NULLPTR);
    unsigned int getSolutionSize() const;
    long double evaluateSolution(const std::vector<long double> &s) const;
    void showSolution(const std::vector<long double> &s);
    std::vector<long double> crossover(const std::vector<long double> &a, const std::vector<long double> &b);
    void mutate(std::vector<long double> &);
    std::vector<long double> getRandomSolution() const;
};

#endif // FUNCTIONFITTING_H
