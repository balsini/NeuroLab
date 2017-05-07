#include "memory_allocation.h"

#include <QDebug>

#include <QGraphicsSceneMouseEvent>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QGraphicsView>

#include <algorithm>
#include <cmath>

#include "WATERS/src/main_waters.h"
#include "WATERS/src/RT.h"
#include "WATERS/src/genetic.h"

static const int radius = 8;
static QBrush brush;

MemoryAllocation::MemoryAllocation(QObject *parent) :
  QGraphicsScene(parent),
  RAM(LRAM_0 | LRAM_1 | LRAM_2 | LRAM_3 | GRAM),
  core(0)
{
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::red);

  initialize_waters_data();
}

unsigned int MemoryAllocation::getSolutionSize() const
{
  return get_genes_size_waters_GA();
}

double MemoryAllocation::evaluateSolution(const std::vector<Label> &s) const
{
  return computeResponseTime(s);
}

void MemoryAllocation::refreshView()
{
  int ram_occupancy[] = {0,0,0,0,0};
  QGraphicsView *view = this->views().first();
  int w = view->width() - 3;
  int h = view->height() - 3;

  //qDebug() << "Solution found, window size: [" << w << " - " << h << "]";

  unsigned int columns = floor(sqrt(lastSolution.size()));
  unsigned int rows = ceil(sqrt(lastSolution.size()));

  //qDebug() << "Matrix size: [" << rows << " - " << columns << "]";

  qreal rect_width = static_cast<double>(w) / columns;
  qreal rect_height = static_cast<double>(h) / rows;

  QGraphicsItem *to_add;

  this->clear();

  unsigned int counter = 0;
  for (unsigned int i=0; i<rows; ++i) {
    for (unsigned int j=0; j<columns; ++j) {
      if (counter >= lastSolution.size())
        goto exitLoop;

      QPen pen;
      QBrush brush(Qt::SolidPattern);
      QColor color;

      //color.setRgbF(1.0, 0, 0);

      if (((lastSolution.at(counter).used_by_CPU & this->core) != this->core)
          || ((lastSolution.at(counter).ram & this->RAM) == 0)) {
        color.setRgbF(0, 0, 0);
      } else {
        switch(lastSolution.at(counter).ram) {
        case 	LRAM_0:
          color.setRgbF(1, 1, 0);
          ++ram_occupancy[0];
          break;
        case 	LRAM_1:
          color.setRgbF(1, 0, 1);
          ++ram_occupancy[1];
          break;
        case 	LRAM_2:
          color.setRgbF(0, 0, 1);
          ++ram_occupancy[2];
          break;
        case 	LRAM_3:
          color.setRgbF(0, 1, 0);
          ++ram_occupancy[3];
          break;
        case 	GRAM:
          color.setRgbF(1, 0, 0);
          ++ram_occupancy[4];
          break;
        default:
          qDebug() << "Error: wrong switch in refreshView()";
          break;
        }
      }

      brush.setColor(color);

      to_add = addRect(0, 0, rect_width, rect_height, pen, brush);

      to_add->setPos(j * rect_width, i * rect_height);

      ++counter;
    }
  }

exitLoop:
  emit RAM_counted(ram_occupancy[0],
      ram_occupancy[1],
      ram_occupancy[2],
      ram_occupancy[3],
      ram_occupancy[4]);
}

void MemoryAllocation::showSolution(const std::vector<Label> &newSolution)
{
  lastSolution = newSolution;

  refreshView();
}

std::vector<Label> MemoryAllocation::crossover(const std::vector<Label> &a, const std::vector<Label> &b)
{
  return crossover_waters_GA(a, b);
}

void MemoryAllocation::mutate(std::vector<Label> &c)
{
  mutatate_chromosome_waters_GA(c);
}

std::vector<Label> MemoryAllocation::getRandomSolution() const
{
  return getRandomSolution_waters_GA();
}

void MemoryAllocation::setRAM(uint8_t r)
{
  this->RAM = r;
  refreshView();
}

void MemoryAllocation::setCore(uint8_t c)
{
  this->core = c;
  refreshView();
}
