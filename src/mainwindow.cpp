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

void MainWindow::on_pushButton_clicked()
{
  //auto p = tsp->getTargets();
  //tsp->setPath(g->randomize());

  g = new GeneticAlgorithm<int>(ui->GA_epochs->text().toInt(),
                                ui->GA_population->text().toInt(),
                                ui->GA_survivors->value() / 100.0,
                                ui->GA_identical->value() / 100.0,
                                ui->GA_recombine->value() / 100.0);
  g->setProblem(tsp);
  g->setErrorPlot(ui->GA_errorPlot);
  ui->GA_errorPlot->clear();

  try {
    ui->GA_cost->setValue(g->run());
  } catch (std::string e) {
    std::cerr << e << std::endl;
  }

  delete g;
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
