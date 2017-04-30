#ifndef TSP_H
#define TSP_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <chrono>
#include <vector>

#include "optimizationproblem.h"

typedef std::pair<int, int> Coordinate;

class TSP : public QGraphicsScene, public GAOptimizationProblem<int>
{
    Q_OBJECT

    std::vector<QGraphicsItem *> targets;
    std::vector<QGraphicsItem *> steps;

  public:
    TSP(QObject *parent = Q_NULLPTR);
    std::vector<Coordinate> getTargets();
    void setPath(const std::vector<Coordinate> &steps);
    unsigned int getSolutionSize() const { return targets.size(); }
    double evaluateSolution(const std::vector<int> &s) const;
    void showSolution(const std::vector<int> &s);
    std::vector<int> crossover(const std::vector<int> &a, const std::vector<int> &b);
    std::vector<int> getRandomSolution() const;

  public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // TSP_H
