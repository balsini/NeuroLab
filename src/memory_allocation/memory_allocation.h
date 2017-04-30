#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <chrono>

#include <QResizeEvent>

#include "optimizationproblem.h"

typedef std::pair<int, int> Coordinate;

enum Memory { LRAM0, LRAM1, LRAM2, LRAM3, GRAM };

class MemoryAllocation : public QGraphicsScene, public GAOptimizationProblem<int>
{
    Q_OBJECT

    std::vector<QGraphicsItem *> targets;
    std::vector<QGraphicsItem *> steps;

  public:
    MemoryAllocation(QObject *parent = Q_NULLPTR);
    std::vector<Coordinate> getTargets();
    unsigned int getSolutionSize() const { return targets.size(); }
    double evaluateSolution(const std::vector<int> &s) const;
    void showSolution(const std::vector<int> &s);
    std::vector<int> crossover(const std::vector<int> &a, const std::vector<int> &b);
    std::vector<int> getRandomSolution() const;

  public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void resizeEvent(QResizeEvent *event);
};

#endif // MEMORY_ALLOCATION_H
