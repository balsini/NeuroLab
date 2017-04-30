#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "matfun.h"
#include "hopfield.h"
#include "geneticalgorithm.h"

#include <functional>
#include <QString>

#include <QDebug>

Hopfield h(16*16);



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  tsp = new TSP(this);
  ui->TSPView->setScene(tsp);

  memory_allocation = new MemoryAllocation(this);
  ui->MemAllocView->setScene(memory_allocation);

  ui->GA_identical->setValue(5);
  ui->GA_recombine->setValue(20);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_hopfieldStep_clicked()
{
  h.step();
  h.printState(16, 16);
}

void MainWindow::on_hopfieldAddNoise_clicked()
{
  h.addNoise(10);
}

void MainWindow::on_hopfieldLoadImage_clicked()
{
  h.loadData("/home/alessio/git/NeuroLab/data/hopfield_00.txt");
}

void MainWindow::on_GA_identical_valueChanged(double v)
{
  ui->GA_mutate->setValue(100 - v - ui->GA_recombine->value());
  if (ui->GA_mutate->value() == 0) {
    ui->GA_recombine->setValue(100 - v);
  }
}

void MainWindow::on_GA_recombine_valueChanged(double v)
{
  ui->GA_mutate->setValue(100 - ui->GA_identical->value() - v);
  if (ui->GA_mutate->value() == 0) {
    ui->GA_identical->setValue(100 - v);
  }
}

void MainWindow::on_GA_run_clicked()
{
  //auto p = tsp->getTargets();
  //tsp->setPath(g->randomize());

  g = new GeneticAlgorithm_Specialized<int>(ui->GA_epochs->text().toInt(),
                                ui->GA_population->text().toInt(),
                                ui->GA_survivors->value() / 100.0,
                                ui->GA_identical->value() / 100.0,
                                ui->GA_recombine->value() / 100.0);

  qDebug() << "Current tab index: " << ui->geneticTab->currentIndex();

  switch (ui->geneticTab->currentIndex()) {
    case 0:
      dynamic_cast<GeneticAlgorithm_Specialized<int> *>(g)->setProblem(tsp);
      break;
    case 1:
      dynamic_cast<GeneticAlgorithm_Specialized<int> *>(g)->setProblem(memory_allocation);
      break;
    default:
      delete g;
      return;
  }

  ui->GA_errorPlot->clear();
  //g->setErrorPlot(ui->GA_errorPlot);

  GA_Thread *workerThread = new GA_Thread;
  workerThread->setGA(g);
  connect(workerThread, &GA_Thread::resultReady, this, &MainWindow::GA_result_ready);
  connect(workerThread, &GA_Thread::newBestResult, this, &MainWindow::GA_new_best);
  connect(workerThread, &GA_Thread::finished, workerThread, &QObject::deleteLater);
  workerThread->start();
}

void MainWindow::GA_new_best(GeneticAlgorithm *g, double d)
{
  g->showSolution();
  ui->GA_cost->setValue(d);
  ui->GA_errorPlot->addEpochMinValue(d);
  ui->GA_errorPlot->plot();
}

void MainWindow::GA_result_ready(GeneticAlgorithm *g)
{
  g->showSolution();

  delete g;
}
