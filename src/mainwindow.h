#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "tsp/tsp.h"
#include "memory_allocation/memory_allocation.h"
#include "geneticalgorithm.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    TSP *tsp;
    MemoryAllocation *memory_allocation;
    GeneticAlgorithm *g;
    GA_Thread *workerThread;

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_hopfieldStep_clicked();
    void on_hopfieldAddNoise_clicked();
    void on_hopfieldLoadImage_clicked();
    void on_GA_identical_valueChanged(double);
    void on_GA_recombine_valueChanged(double);
    void on_GA_run_clicked();
    void on_GA_stop_clicked();
    void GA_new_best(GeneticAlgorithm *, double);
    void GA_result_ready(GeneticAlgorithm *);

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
