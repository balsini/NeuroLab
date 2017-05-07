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

struct GA_settings_t {
    unsigned int epochs;
    unsigned int population_size;
    unsigned int survivors;
    unsigned int identical;
    unsigned int recombine_from;
    unsigned int recombine_to;
    unsigned int mutate_from;
    unsigned int mutate_to;
};

class GeneticAlgorithm
{
  protected:
    GA_settings_t _gas;
    unsigned int _genes;

  public:
     GeneticAlgorithm(GA_settings_t g) :
      _gas(g) {}
    virtual ~GeneticAlgorithm() {}

    virtual std::pair<double, double> run_init() = 0;
    virtual std::pair<double, double> run_step() = 0;
    unsigned int get_epochs() const { return _gas.epochs; }
    virtual void reorder() = 0;
    virtual void removeWorst() = 0;
    virtual void crossover() = 0;
    virtual void mutation() = 0;
    virtual void computeAnySolution() = 0;
    virtual double evaluate() = 0;
    virtual void showSolution() = 0;
    virtual void clear() = 0;
    virtual void printInfo() {}
    virtual void printPopulation() {}
};

template <class Gene>
class GeneticAlgorithm_Specialized : public GeneticAlgorithm
{
    typedef std::vector<Gene> Chromosome;

    std::vector<std::pair<Chromosome, double>> population;
    GAOptimizationProblem<Gene> *_problem;

  public:
    GeneticAlgorithm_Specialized(GA_settings_t g) :
      GeneticAlgorithm(g)
    {}

    void setProblem(GAOptimizationProblem<Gene> *p)
    {
      _problem = p;
    }

    void clear()
    {
      population.clear();
    }

    double evaluate()
    {
      double sum = 0.0;

      for (auto &p : population) {
        p.second = _problem->evaluateSolution(p.first);
        sum += p.second / population.size();
      }

      return sum;
    }

    void reorder()
    {
      std::sort(population.begin(), population.end(),
                [&](const std::pair<Chromosome, double> &a, const std::pair<Chromosome, double> &b) {
        return a.second < b.second;
      });
    }

    void removeWorst()
    {
      population.erase(population.end() - _gas.population_size + _gas.survivors, population.end());
    }

    void crossover()
    {
      std::random_device rd;
      std::mt19937 generator(rd());
      std::uniform_int_distribution<int> d(_gas.recombine_from, _gas.recombine_to);

      while (population.size() < _gas.population_size) {
        population.push_back(std::make_pair(_problem->crossover(population[d(generator)].first,
                                                                population[d(generator)].first),
                                            0.0));
      }
    }

    void mutation()
    {
      for (unsigned int i=_gas.mutate_from; i<_gas.mutate_to; ++i)
        _problem->mutate(population[i].first);
    }

    std::pair<double, double> run_init()
    {
      double mean;

      population.resize(_gas.population_size);
      _genes = _problem->getSolutionSize();

      if (_genes < 2)
        throw(std::string("Problem size too small"));

      for (auto &p : population) {
        p.first.clear();
        p.first.resize(_genes);
      }

      printInfo();

      computeAnySolution();
      mean = evaluate();
      reorder();

      return std::make_pair(population.front().second, mean);
    }

    std::pair<double, double> run_step()
    {
      double mean;

      removeWorst();
      crossover();
      mutation();

      mean = evaluate();
      reorder();

      return std::make_pair(population.front().second, mean);
    }

    void computeAnySolution()
    {
      for (auto &p : population)
        p.first = _problem->getRandomSolution();
    }

    void showSolution()
    {
      _problem->showSolution(population.front().first);
    }

    void printInfo()
    {
      std::cout << "Population:\t" << population.size() << std::endl;
      std::cout << "Gene Type:\t" << typeid(Gene).name() << std::endl;
      std::cout << "Genes:\t" << _genes << std::endl;
      std::cout << "Survivors:\t" << _gas.survivors << std::endl;
      std::cout << "Identical:\t" << _gas.identical << std::endl;
      std::cout << "Recombine from:\t" << _gas.recombine_from << std::endl;
      std::cout << "Recombine to:\t" << _gas.recombine_to << std::endl;
      std::cout << "Mutate from:\t" << _gas.mutate_from << std::endl;
      std::cout << "Mutate to:\t" << _gas.mutate_to << std::endl;
      std::cout << "----------------" << std::endl;
    }

    void printSolution(const Chromosome &c)
    {
      for (auto const &v : c)
        std::cout << v << " ";
    }

    void printPopulation()
    {
      unsigned int counter = 0;

      std::cout << "Population:" << std::endl;
      for (auto const &p : population) {
        std::cout << counter++ << ")\t";
        printSolution(p.first);

        std::cout << "\t ( " << _problem->evaluateSolution(p.first) << " )" << std::endl;
      }
      std::cout << "----------------" << std::endl;
    }
};

class GA_Thread : public QThread
{
    Q_OBJECT

    bool go;
    GeneticAlgorithm *ga;

  public:
    void setGA(GeneticAlgorithm *g)
    {
      ga = g;
    }
    void stop()
    {
      go = false;
    }
    void run() override {
      go = true;
      try {
        emit newBestResult(ga, ga->run_init());
        for (unsigned int i=1; go && i<ga->get_epochs(); ++i) {
          emit newBestResult(ga, ga->run_step());
        }
      } catch (std::string e) {
        std::cerr << e << std::endl;
      }
      emit resultReady(ga);
    }
  signals:
    void resultReady(GeneticAlgorithm *g);
    void newBestResult(GeneticAlgorithm *g, std::pair<double, double>);
};

#endif // GENETICALGORITHM_H
