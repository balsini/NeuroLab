#ifndef TSP_H
#define TSP_H

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <chrono>

#include "optimizationproblem.h"

typedef std::pair<int, int> Coordinate;

class TSP : public QGraphicsScene, public GeneticOptimizationProblem<int>
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

    void showSolution(const std::vector<int> &s)
    {
      int x, y;
      std::vector<Coordinate> steps;

      for (int p : s) {
        x = targets[p]->x();
        y = targets[p]->y();

        steps.push_back(std::make_pair(x, y));
      }
      setPath(steps);
    }

    std::vector<int> crossover(const std::vector<int> &a, const std::vector<int> &b)
    {
      std::vector<int> ret;
      std::vector<int> sub_sol;
      static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      static std::default_random_engine generator(seed);
      std::uniform_int_distribution<int> d1(0, a.size() - 2);
      unsigned int c1, c2;
      unsigned int i;

      c1 = d1(generator);

      std::uniform_int_distribution<int> d2(c1 + 1, targets.size() - 1);

      c2 = d2(generator);

      for (i=c1; i<c2; ++i)
        sub_sol.push_back(a[i]);

      i = 0;
      while (ret.size() < c1) {
        if (std::find(sub_sol.begin(), sub_sol.end(), b[i]) == sub_sol.end())
          ret.push_back(b[i]);
        ++i;
      }

      for (auto v : sub_sol)
        ret.push_back(v);

      while (ret.size() < a.size()) {
        if (std::find(sub_sol.begin(), sub_sol.end(), b[i]) == sub_sol.end())
          ret.push_back(b[i]);
        ++i;
      }

      return ret;
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
