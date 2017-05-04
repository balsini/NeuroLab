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

    void update_memory_ram_chosen();
    void update_core_chosen();

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
    void GA_new_best(GeneticAlgorithm *, std::pair<double, double>);
    void GA_result_ready(GeneticAlgorithm *);
    void on_LRAM_0_checkbox_clicked();
    void on_LRAM_1_checkbox_clicked();
    void on_LRAM_2_checkbox_clicked();
    void on_LRAM_3_checkbox_clicked();
    void on_GRAM_checkbox_clicked();
    void on_core_0_checkbox_clicked();
    void on_core_1_checkbox_clicked();
    void on_core_2_checkbox_clicked();
    void on_core_3_checkbox_clicked();

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
