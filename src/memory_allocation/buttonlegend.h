#ifndef BUTTONLEGEND_H
#define BUTTONLEGEND_H

#include <QPushButton>

#include <QDebug>

class ButtonLegend : public QPushButton
{
    Q_OBJECT

  public:
    explicit ButtonLegend(QWidget *parent = 0);

  signals:

  public slots:
    void showNumericalValue(int v);
};

#endif // BUTTONLEGEND_H
