#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QDebug>

#include <vector>
#include <iostream>
#include <typeinfo>
#include <functional>
#include <chrono>

#include "optimizationproblem.h"
#include "gaerrorplot.h"

template <class Gene>
class GeneticAlgorithm
{
    typedef std::vector<Gene> Chromosome;
    std::vector<Chromosome> population;

    unsigned int _size;
    unsigned int _genes;
    unsigned int _survivors;
    unsigned int _identical;
    unsigned int _recombine;
    unsigned int _mutate;
    unsigned int _kill;
    unsigned int _epochs;

    GAOptimizationProblem<Gene> *_problem;
    GAErrorPlot *_plot;

  public:
    GeneticAlgorithm(unsigned int epochs,
                     unsigned int size,
                     double survivors,
                     double identical,
                     double recombine)
    {
      _epochs = epochs;
      _size = size;
      _survivors = size * survivors;
      _identical = _survivors * identical;
      _recombine = _survivors * recombine;
      _mutate = _survivors - _identical - _recombine;
      _kill = _size - _survivors;

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

    double run()
    {
      qDebug() << "GeneticAlgorithm::run()";

      population.resize(_size);
      _genes = _problem->getSolutionSize();

      if (_genes < 2)
        throw(std::string("Problem size too small"));

      for (auto &p : population) {
        p.clear();
        p.resize(_genes);
      }

      computeAnySolution();

      printInfo();
      //printPopulation();

      for (unsigned int i=0; i<_epochs; ++i) {
        _plot->addEpochMinValue(_problem->evaluateSolution(population.front()));

        removeWorst();
        crossover();
        mutation();

        reorder();
      }
      _problem->showSolution(population.front());
      _plot->plot();
      //printPopulation();

      return _problem->evaluateSolution(population.front());
    }

    void computeAnySolution()
    {
      for (auto &p : population)
        p = _problem->getRandomSolution();
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

    void setProblem(GAOptimizationProblem<Gene> *p) { _problem = p; }
    void setErrorPlot(GAErrorPlot *p) { _plot = p; }
};

#endif // GENETICALGORITHM_H
