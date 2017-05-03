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
  viewKind(GLOBAL_RAM_VIEW),
  RAM(LRAM_0),
  core(1)
{
  brush.setStyle(Qt::SolidPattern);
  brush.setColor(Qt::red);

  initialize_waters_data();
}

double MemoryAllocation::evaluateSolution(const std::vector<Label> &s) const
{
  return computeResponseTime(s);
}

void MemoryAllocation::refreshView()
{

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
  switch (viewKind) {
    case RAM_USED_BY_CPU_VIEW:
    case GLOBAL_RAM_VIEW:
      for (unsigned int i=0; i<rows; ++i) {
        for (unsigned int j=0; j<columns; ++j) {
          if (counter >= lastSolution.size())
            return;

          QPen pen;
          QBrush brush(Qt::SolidPattern);
          QColor color;

          //color.setRgbF(1.0, 0, 0);

          switch(lastSolution.at(counter).ram) {
            case 	LRAM_0:
              color.setRgbF(1, 1, 0);
              break;
            case 	LRAM_1:
              color.setRgbF(1, 0, 1);
              break;
            case 	LRAM_2:
              color.setRgbF(0, 0, 1);
              break;
            case 	LRAM_3:
              color.setRgbF(0, 1, 0);
              break;
            case 	GRAM:
              color.setRgbF(1, 0, 0);
              break;
            default:
              qDebug() << "Error: wrong switch in refreshView()";
              break;
          }

          if (viewKind == RAM_USED_BY_CPU_VIEW) {
            if ((lastSolution.at(counter).used_by_CPU & this->core) == 0) {
              color.setRgbF(0, 0, 0);
            }
          }

          brush.setColor(color);

          to_add = addRect(0, 0, rect_width, rect_height, pen, brush);

          to_add->setPos(j * rect_width, i * rect_height);

          ++counter;
        }
      }
      break;

    case CPU_USED_BY_RAM_VIEW:
      for (unsigned int i=0; i<rows; ++i) {
        for (unsigned int j=0; j<columns; ++j) {
          if (counter >= lastSolution.size())
            return;

          QPen pen;
          QBrush brush(Qt::SolidPattern);
          QColor color;

          //color.setRgbF(1.0, 0, 0);

          if (lastSolution.at(counter).ram == this->RAM) {
            if (lastSolution.at(counter).used_by_CPU & this->core) {
                color.setRgbF(0, 0, 1);
            }
          } else {
            color.setRgbF(0, 0, 0);
          }

          brush.setColor(color);

          to_add = addRect(0, 0, rect_width, rect_height, pen, brush);

          to_add->setPos(j * rect_width, i * rect_height);

          ++counter;
        }
      }
      break;
    default:
      break;
  }
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

void MemoryAllocation::resizeEvent(int w, int h)
{
  /*
  qDebug() << "sceneRectChanged(const QRectF &rect)" << event->size();

  qreal rect_width = event->size().width() / 100.0;
  qreal rect_height = event->size().height() / 100.0;

  QGraphicsItem *to_add;

  this->clear();

  for (unsigned int i=0; i<100; ++i) {
    for (unsigned int j=0; j<100; ++j) {
      to_add = addRect(0, 0, rect_width, rect_height);

      to_add->setPos(j * rect_width, i * rect_height);
    }
  }
  */
}

void MemoryAllocation::setView(ViewKind v)
{
  viewKind = v;
  refreshView();
}

void MemoryAllocation::setRAM(int r)
{
  this->RAM = static_cast <RAM_LOC>(1 << r);
  refreshView();
}

void MemoryAllocation::setCore(int c)
{
  this->core = 1 << c;
  refreshView();
}
