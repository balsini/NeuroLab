#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <iostream>
#include <typeinfo>
#include <functional>
#include <chrono>

#include <QObject>
#include <QWidget>
#include <QThread>

#include "optimizationproblem.h"

class GeneticAlgorithm
{
  protected:
    unsigned int _epochs;
    unsigned int _size;
    unsigned int _survivors;
    unsigned int _identical;
    unsigned int _recombine;
    unsigned int _mutate;
    unsigned int _kill;
    unsigned int _genes;

  public:
    GeneticAlgorithm(unsigned int epochs,
                     unsigned int size,
                     double survivors,
                     double identical,
                     double recombine) :
      _epochs(epochs),
      _size(size),
      _survivors(size * survivors),
      _identical(_survivors * identical),
      _recombine(_survivors * recombine),
      _mutate(_survivors - _identical - _recombine),
      _kill(_size - _survivors) {}
    virtual ~GeneticAlgorithm() {}

    virtual double run_init() = 0;
    virtual double run_step() = 0;
    unsigned int get_epochs() const { return _epochs; }
    virtual void reorder() = 0;
    virtual void removeWorst() = 0;
    virtual void crossover() = 0;
    virtual void mutation() = 0;
    virtual void computeAnySolution() = 0;
    virtual void showSolution() = 0;
    virtual void clear() = 0;
    virtual void printInfo() {}
    virtual void printPopulation() {}
};

template <class Gene>
class GeneticAlgorithm_Specialized : public GeneticAlgorithm
{
    typedef std::vector<Gene> Chromosome;
    std::vector<Chromosome> population;
    GAOptimizationProblem<Gene> *_problem;

  public:
    GeneticAlgorithm_Specialized(unsigned int epochs,
                                 unsigned int size,
                                 double survivors,
                                 double identical,
                                 double recombine) :
      GeneticAlgorithm(epochs, size, survivors, identical, recombine)
    {}
    void setProblem(GAOptimizationProblem<Gene> *p) { _problem = p; }
    void clear()
    {
      population.clear();
    }
    void reorder()
    {
      std::sort(population.begin(), population.end(),
                [&](const Chromosome &a, const Chromosome &b) {
        return _problem->evaluateSolution(a) < _problem->evaluateSolution(b);
      });
    }
    void removeWorst()
    {
      for (unsigned int i=0; i<_kill; ++i)
        population.pop_back();
    }
    void crossover()
    {
      static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      static std::default_random_engine generator(seed);
      std::uniform_int_distribution<int> d1(0, _identical);
      std::uniform_int_distribution<int> d2(0, _identical);

      while (population.size() < _size) {
        population.push_back(_problem->crossover(population[d1(generator)],
                             population[d2(generator)]));
      }
    }
    void mutation()
    {
      static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
      static std::default_random_engine generator(seed);
      std::uniform_int_distribution<int> d(0, _genes - 1);
      int p1, p2, x;

      for (unsigned int i=_identical; i<_identical+_mutate; ++i) {
        Chromosome &c = population[i];

        p1 = d(generator);
        p2 = d(generator);
        x = c[p1];
        c[p1] = c[p2];
        c[p2] = x;
      }
    }
    double run_init()
    {
      population.resize(_size);
      _genes = _problem->getSolutionSize();

      if (_genes < 2)
        throw(std::string("Problem size too small"));

      for (auto &p : population) {
        p.clear();
        p.resize(_genes);
      }

      printInfo();

      computeAnySolution();
      reorder();

      return _problem->evaluateSolution(population.front());
    }

    double run_step()
    {
      removeWorst();
      crossover();
      mutation();

      reorder();

      return _problem->evaluateSolution(population.front());
    }

void computeAnySolution()
{
  for (auto &p : population)
    p = _problem->getRandomSolution();
}
void showSolution()
{
  _problem->showSolution(population.front());
}
void printInfo()
{
  std::cout << "Population:\t" << population.size() << std::endl;
  std::cout << "Gene Type:\t" << typeid(Gene).name() << std::endl;
  std::cout << "Genes:\t" << _genes << std::endl;
  std::cout << "Survivors:\t" << _survivors << std::endl;
  std::cout << "Identical:\t" << _identical << std::endl;
  std::cout << "Recombine:\t" << _recombine << std::endl;
  std::cout << "Mutate:\t" << _mutate << std::endl;
  std::cout << "----------------" << std::endl;
}
void printSolution(const Chromosome &c)
{
  for (auto v : c)
    std::cout << v << " ";
}

void printPopulation()
{
  unsigned int counter = 0;

  std::cout << "Population:" << std::endl;
  for (auto p : population) {
    std::cout << counter++ << ")\t";
    printSolution(p);

    std::cout << "\t ( " << _problem->evaluateSolution(p) << " )" << std::endl;
  }
  std::cout << "----------------" << std::endl;
}
};

class GA_Thread : public QThread
{
    Q_OBJECT

    GeneticAlgorithm *ga;

  public:
    void setGA(GeneticAlgorithm *g)
    {
      ga = g;
    }
    void run() override {
      try {
        emit newBestResult(ga, ga->run_init());
        for (unsigned int i=1; i<ga->get_epochs(); ++i) {
          emit newBestResult(ga, ga->run_step());
        }
      } catch (std::string e) {
        std::cerr << e << std::endl;
      }
      emit resultReady(ga);
    }
  signals:
    void resultReady(GeneticAlgorithm *g);
    void newBestResult(GeneticAlgorithm *g, double);
};

#endif // GENETICALGORITHM_H
