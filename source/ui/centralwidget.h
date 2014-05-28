#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QTabWidget>
#include <QPlainTextEdit>
#include <QFileInfo>
#include "qwt_plot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_curve.h"
#include "qwt_legend.h"
#include "myglwidget.h"

class CentralWidget : public QTabWidget
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = 0);

    bool setProFile(const QString &proFilePath);
private:
    void initTmpPlotAndGL();
private:
    QPlainTextEdit *m_proFileWidget;
    QWidget *m_solutionWidget;
    QWidget *m_modelWidget;
};

#endif // CENTRALWIDGET_H
