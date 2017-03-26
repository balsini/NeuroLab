#ifndef OPTIMIZATIONPROBLEM_H
#define OPTIMIZATIONPROBLEM_H

#include <vector>

template<class T>
class OptimizationProblem
{
  protected:
    OptimizationProblem() {}
  public:
    virtual unsigned int getSolutionSize() const = 0;
    virtual std::vector<T> getRandomSolution() const = 0;
    virtual double evaluateSolution(const std::vector<T> &) const = 0;
    virtual void showSolution(const std::vector<T> &) = 0;
};

template<class T>
class GAOptimizationProblem : public OptimizationProblem<T>
{
  protected:
    GAOptimizationProblem() {}
  public:
    virtual unsigned int getSolutionSize() const = 0;
    virtual std::vector<T> getRandomSolution() const = 0;
    virtual double evaluateSolution(const std::vector<T> &) const = 0;
    virtual std::vector<int> crossover(const std::vector<T> &,
                                       const std::vector<T> &) = 0;
};

#endif // OPTIMIZATIONPROBLEM_H
