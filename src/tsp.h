#ifndef TSP_H
#define TSP_H

#include <QGraphicsScene>

class TSP : public QGraphicsScene
{
    Q_OBJECT

  public:
    TSP(QObject *parent = Q_NULLPTR);

  public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // TSP_H
