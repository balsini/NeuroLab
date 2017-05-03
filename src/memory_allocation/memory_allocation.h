#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include <vector>
#include <chrono>
#include <cstdint>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QResizeEvent>

#include "optimizationproblem.h"
#include "WATERS/src/milpData.h"
#include "WATERS/src/genetic.h"

enum ViewKind { GLOBAL_RAM_VIEW, RAM_USED_BY_CPU_VIEW };

class MemoryAllocation : public QGraphicsScene, public GAOptimizationProblem<Label>
{
    Q_OBJECT

    ViewKind viewKind;
    std::vector<Label> lastSolution;
    uint8_t RAM;
    int core;

  public:
    MemoryAllocation(QObject *parent = Q_NULLPTR);
    unsigned int getSolutionSize() const { return get_genes_size_waters_GA(); }
    double evaluateSolution(const std::vector<Label> &s) const;
    void showSolution(const std::vector<Label> &newSolution);
    std::vector<Label> crossover(const std::vector<Label> &a, const std::vector<Label> &b);
    void mutate(std::vector<Label> &c);
    std::vector<Label> getRandomSolution() const;
    void setView(ViewKind v);
    void setRAM(uint8_t r);
    void setCore(int c);
    void refreshView();

  signals:
    void RAM_counted(int, int, int, int, int);
};

#endif // MEMORY_ALLOCATION_H
