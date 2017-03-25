#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "matfun.h"
#include "hopfield.h"
#include "geneticalgorithm.h"

#include <functional>
#include <QDebug>

Hopfield h(16*16);



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  tsp = new TSP(this);

  ui->TSPView->setScene(tsp);

  g = new GeneticAlgorithm<int>(20,
                                0.8,
                                0.1,
                                0.8);
  g->setProblem(tsp);
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
  g->run();
}
