#ifndef TSP_H
#define TSP_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <chrono>

#include "optimizationproblem.h"

typedef std::pair<int, int> Coordinate;

class TSP : public QGraphicsScene, public OptimizationProblem<int>
{
    Q_OBJECT

    std::vector<QGraphicsItem *> targets;
    std::vector<QGraphicsItem *> steps;

  public:
    TSP(QObject *parent = Q_NULLPTR);
    std::vector<Coordinate> getTargets();
    void setPath(const std::vector<Coordinate> &steps);
    unsigned int getSolutionSize() const { return targets.size(); }

    /*
     * The solution vector represents the order in which the targets
     * are going to be visited
     */
    double evaluateSolution(const std::vector<int> &s) const
    {
      double _cost = 0;

      for (unsigned int i=0; i<s.size(); ++i) {
        int x1, x2, y1, y2;

        x1 = targets[s[i]]->x();
        x2 = targets[s[(i + 1) % s.size()]]->x();

        y1 = targets[s[i]]->y();
        y2 = targets[s[(i + 1) % s.size()]]->y();

        _cost += sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
      }

      return _cost;
    }


    std::vector<int> getRandomSolution() const
    {
      static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      static std::default_random_engine generator(seed);
      std::uniform_int_distribution<int> distribution(0, targets.size() - 1);

      std::vector<int> s;

      for (unsigned int i=0; i<targets.size(); ++i)
        s.push_back(i);

      for (unsigned int i=0; i<s.size(); ++i)
        std::swap(s[i], s[distribution(generator)]);

      return s;
    }

  public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // TSP_H
