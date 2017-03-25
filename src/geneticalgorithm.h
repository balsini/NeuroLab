#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <QDebug>

#include <vector>
#include <iostream>
#include <typeinfo>
#include <functional>
#include <chrono>

#include "optimizationproblem.h"

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

    OptimizationProblem<Gene> *_problem;

  public:
    GeneticAlgorithm(unsigned int size,
                     double survivors,
                     double identical,
                     double recombine)
    {
      _size = size;
      _survivors = size * survivors;
      _identical = _survivors * identical;
      _recombine = _survivors * recombine;
      _mutate = _survivors - _identical - _recombine;

      population.clear();
    }

    void reorder()
    {
      std::sort(population.begin(), population.end(),
                [&](const Chromosome &a, const Chromosome &b) {
        return _problem->evaluateSolution(a) < _problem->evaluateSolution(b);
      });
    }

    void run()
    {
      qDebug() << "GeneticAlgorithm::run()";

      population.resize(_size);
      _genes = _problem->getSolutionSize();
      for (auto &p : population) {
        p.clear();
        p.resize(_genes);
      }

      computeAnySolution();

      printInfo();
      printPopulation();

      for (unsigned int i=0; i<1; ++i) {
        reorder();
        printPopulation();

        TODO
      }
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

    void setProblem(OptimizationProblem<Gene> *p) { _problem = p; }
};

#endif // GENETICALGORITHM_H
