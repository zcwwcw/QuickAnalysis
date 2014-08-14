#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QApplication>
#include "centralwidget.h"
#include "propertydockwidget.h"
#include "casetreeview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void scriptExcuteActSlot();

    void languageChineseActSlot();
    void languageEnglishActSlot();

    void systemExitActSlot();

    void helpAboutActSlot();
private:
    void initUI();
};

#endif // MAINWINDOW_H
