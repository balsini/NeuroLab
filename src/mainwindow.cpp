#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "matfun.h"
#include "hopfield.h"
#include "geneticalgorithm.h"
#include "memory_allocation/WATERS/src/milpData.h"

#include <functional>
#include <QString>

#include <QDebug>

Hopfield h(16*16);



MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  g(nullptr),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  tsp = new TSP(this);
  ui->TSPView->setScene(tsp);

  memory_allocation = new MemoryAllocation(this);
  ui->MemAllocView->setScene(memory_allocation);
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

void MainWindow::on_GA_run_clicked()
{
  //auto p = tsp->getTargets();
  //tsp->setPath(g->randomize());

  ui->GA_run->setEnabled(false);
  ui->GA_stop->setEnabled(true);

  if (g) {
    delete g;
    g = nullptr;
  }

  qDebug() << "Current tab index: " << ui->geneticTab->currentIndex();

  GA_settings_t gas;

  gas.epochs = ui->GA_epochs->text().toInt();
  gas.population_size = ui->GA_population->text().toInt();
  gas.survivors = ui->GA_survivors->value() / 100.0 * gas.population_size;
  gas.recombine_from = ui->GA_recombine_from->value() / 100.0 * gas.population_size;
  gas.recombine_to = ui->GA_recombine_to->value() / 100.0 * gas.population_size;
  gas.mutate_from = ui->GA_mutate_from->value() / 100.0 * gas.population_size;
  gas.mutate_to = ui->GA_mutate_to->value() / 100.0 * gas.population_size;

  switch (ui->geneticTab->currentIndex()) {
  case 0:
    g = new GeneticAlgorithm_Specialized<int>(gas);
    dynamic_cast<GeneticAlgorithm_Specialized<int> *>(g)->setProblem(tsp);
    break;
  case 1:
    g = new GeneticAlgorithm_Specialized<Label>(gas);
    dynamic_cast<GeneticAlgorithm_Specialized<Label> *>(g)->setProblem(memory_allocation);
    break;
  default:
    return;
  }

  ui->TSPView->setEnabled(false);
  ui->GA_errorPlot->clear();

  workerThread = new GA_Thread;
  workerThread->setGA(g);
  connect(workerThread, &GA_Thread::resultReady, this, &MainWindow::GA_result_ready);
  connect(workerThread, &GA_Thread::newBestResult, this, &MainWindow::GA_new_best, Qt::BlockingQueuedConnection);
  connect(workerThread, &GA_Thread::finished, workerThread, &QObject::deleteLater);
  workerThread->start();
}

void MainWindow::GA_new_best(GeneticAlgorithm *g, std::pair<double, double> v)
{
  g->showSolution();
  ui->GA_cost->setText(QString::number(v.first, 'g', 12));
  ui->GA_errorPlot->addEpochValues(v.first, v.second);
  ui->GA_errorPlot->plot();
}

void MainWindow::GA_result_ready(GeneticAlgorithm *g)
{
  g->showSolution();

  delete workerThread;

  ui->TSPView->setEnabled(true);
  ui->GA_stop->setEnabled(false);
  ui->GA_run->setEnabled(true);
}

void MainWindow::on_GA_stop_clicked()
{
  workerThread->stop();
}

void MainWindow::update_memory_ram_chosen()
{
  uint8_t ram = 0;

  if (ui->LRAM_0_checkbox->isChecked())
    ram |= LRAM_0;
  if (ui->LRAM_1_checkbox->isChecked())
    ram |= LRAM_1;
  if (ui->LRAM_2_checkbox->isChecked())
    ram |= LRAM_2;
  if (ui->LRAM_3_checkbox->isChecked())
    ram |= LRAM_3;
  if (ui->GRAM_checkbox->isChecked())
    ram |= GRAM;

  ui->MemAllocView->setRAM(ram);
}

void MainWindow::on_LRAM_0_checkbox_clicked()
{
  update_memory_ram_chosen();
}

void MainWindow::on_LRAM_1_checkbox_clicked()
{
  update_memory_ram_chosen();
}

void MainWindow::on_LRAM_2_checkbox_clicked()
{
  update_memory_ram_chosen();
}

void MainWindow::on_LRAM_3_checkbox_clicked()
{
  update_memory_ram_chosen();
}

void MainWindow::on_GRAM_checkbox_clicked()
{
  update_memory_ram_chosen();
}

void MainWindow::update_core_chosen()
{
  uint8_t core = 0;

  if (ui->core_0_checkbox->isChecked())
    core |= 1 << 0;
  if (ui->core_1_checkbox->isChecked())
    core |= 1 << 1;
  if (ui->core_2_checkbox->isChecked())
    core |= 1 << 2;
  if (ui->core_3_checkbox->isChecked())
    core |= 1 << 3;

  ui->MemAllocView->setCore(core);
}

void MainWindow::on_core_0_checkbox_clicked()
{
  update_core_chosen();
}

void MainWindow::on_core_1_checkbox_clicked()
{
  update_core_chosen();
}

void MainWindow::on_core_2_checkbox_clicked()
{
  update_core_chosen();
}

void MainWindow::on_core_3_checkbox_clicked()
{
  update_core_chosen();
}

void MainWindow::on_generateTSP_clicked()
{
  tsp->generateRandom(ui->generateTSPsize->value());
}
