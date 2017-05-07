#ifndef TSPDISPLAY_H
#define TSPDISPLAY_H

#include <QGraphicsView>
#include "tsp.h"

class TSPDisplay : public QGraphicsView
{
    Q_OBJECT

    TSP *myscene;

  public:
    TSPDisplay(QWidget * parent = 0);
    void setScene(QGraphicsScene * scene);

  public slots:
    void clear() {
      myscene->clear();
    }
};

#endif // TSPDISPLAY_H
