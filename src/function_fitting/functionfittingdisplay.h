#ifndef FUNCTIONFITTINGDISPLAY_H
#define FUNCTIONFITTINGDISPLAY_H

#include <QChartView>

#include "functionfitting.h"

using namespace QtCharts;

class FunctionFittingDisplay : public QChartView
{
    Q_OBJECT

    FunctionFitting *myscene;

  public:
    FunctionFittingDisplay(QWidget * parent = 0);
    void setScene(QChart * scene);
    void resizeEvent(QResizeEvent *event);

  public slots:
    void clear() {
      myscene->clear();
    }
};

#endif // FUNCTIONFITTINGDISPLAY_H
