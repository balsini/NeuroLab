#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H

#include <vector>
#include <iostream>
#include <typeinfo>

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

	public:
    GeneticAlgorithm(unsigned int genes,
                     unsigned int size,
                     double survivors,
                     double identical,
                     double recombine) {
      _genes = genes;
      _size = size;
      _survivors = size * survivors;
      _identical = _survivors * identical;
      _recombine = _survivors * recombine;
      _mutate = _survivors - _identical - _recombine;

      population.clear();
      population.resize(size);
      for (auto &p : population) {
        p.clear();
        p.resize(genes);
      }
    }

    void randomize() {
      for (auto i : population) {
        for (auto j : i) {
          j = 1;
        }
      }
    }

    void printInfo() {
      std::cout << "Population:\t" << population.size() << std::endl;
      std::cout << "Gene Type:\t" << typeid(Gene).name() << std::endl;
      std::cout << "Genes:\t" << _genes << std::endl;
      std::cout << "Survivors:\t" << _survivors << std::endl;
      std::cout << "Identical:\t" << _identical << std::endl;
      std::cout << "Recombine:\t" << _recombine << std::endl;
      std::cout << "Mutate:\t" << _mutate << std::endl;
      std::cout << "----------------" << std::endl;
    }

    void printSolution(const Chromosome &c) {
      for (auto v : c)
        std::cout << v << " ";
      std::cout << std::endl;
    }

    void printPopulation() {
      unsigned int counter = 0;

      std::cout << "Population:" << std::endl;
      for (auto p : population) {
        std::cout << counter++ << ")\t";
        printSolution(p);
      }
      std::cout << "----------------" << std::endl;
    }
};

#endif // GENETICALGORITHM_H
