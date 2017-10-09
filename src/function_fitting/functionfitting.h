#ifndef FUNCTIONFITTING_H
#define FUNCTIONFITTING_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QScatterSeries>
#include <QChartView>

#include <chrono>
#include <vector>
#include <map>

#include "optimizationproblem.h"

class FunctionToFit {
    std::map<double, std::vector<double> > _data;
    std::vector<std::pair<long double, long double> > _constraints;
    unsigned int _variables;

  public:
    FunctionToFit();
    long double evaluate(const long double &x, const std::vector<long double> &p) const;
    long double x(unsigned int index) const;
    long double y(unsigned int index) const;
    unsigned int dataSize() const;
    unsigned int variables() const { return _variables; }
    const std::vector<std::pair<long double, long double> > getConstraints() const;
};

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
