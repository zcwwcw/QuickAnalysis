#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUI();
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}

void MainWindow::scriptExcuteActSlot()
{
}

void MainWindow::languageChineseActSlot()
{
}

void MainWindow::languageEnglishActSlot()
{
}

void MainWindow::systemExitActSlot()
{
}

void MainWindow::helpAboutActSlot()
{
    QApplication::aboutQt();
}

void MainWindow::initUI()
{
    //init central widget
    CentralWidget *centralWidget = new CentralWidget(this);
    this->setCentralWidget(centralWidget);

    QDockWidget *caseDock = new QDockWidget(tr("Case Widget"), this);
    CaseTreeView *caseTreeView = new CaseTreeView(caseDock);
    caseDock->setWidget(caseTreeView);
    this->addDockWidget(Qt::LeftDockWidgetArea, caseDock, Qt::Vertical);

    //init property widget
    PropertyDockWidget *propertyDock = new PropertyDockWidget(this);
    this->addDockWidget(Qt::RightDockWidgetArea, propertyDock, Qt::Vertical);

    connect(caseTreeView, SIGNAL(showItemProperties(QString,QList<QVariant>)),
            propertyDock, SLOT(showProperties(QString,QList<QVariant>)));
    connect(caseTreeView, SIGNAL(updateItemProperties(QString,QList<QVariant>)),
            propertyDock, SLOT(updateProperties(QString,QList<QVariant>)));
    connect(propertyDock, SIGNAL(propertyDataChanged(QString,QString)),
            caseTreeView, SLOT(newPropertyData(QString,QString)));
    connect(propertyDock, SIGNAL(propertyCheckStateChanged(QString,Qt::CheckState)),
            caseTreeView, SLOT(newPropertyCheckState(QString,Qt::CheckState)));

    //init main menu
    QMenuBar *mainMenuBar = new QMenuBar(this);
    QMenu *caseMenu = new QMenu(tr("Case"), this);
    mainMenuBar->addMenu(caseMenu);
    QMenu *scriptMenu = new QMenu(tr("Script"), this);
    mainMenuBar->addMenu(scriptMenu);
    QMenu *systemMenu = new QMenu(tr("System"), this);
    QMenu *languageMenu = new QMenu(tr("Language"), systemMenu);
    systemMenu->addMenu(languageMenu);
    mainMenuBar->addMenu(systemMenu);
    QMenu *helpMenu = new QMenu(tr("Help"), this);
    mainMenuBar->addMenu(helpMenu);
    this->setMenuBar(mainMenuBar);

    QAction *newCaseAct = new QAction(QIcon(":/images/add.ico"), tr("New Case"), caseMenu);
    connect(newCaseAct, SIGNAL(triggered()), caseTreeView, SLOT(createCase()));
    QAction *openCaseAct = new QAction(QIcon(":/images/open.ico"), tr("Open Case"), caseMenu);
    connect(openCaseAct, SIGNAL(triggered()), caseTreeView, SLOT(openCase()));
    QAction *closeCaseAct = new QAction(QIcon(":/images/close.png"), tr("Close Case"), caseMenu);
    connect(closeCaseAct, SIGNAL(triggered()), caseTreeView, SLOT(closeCase()));
    QAction *saveCaseAct = new QAction(QIcon(":/images/save.ico"), tr("Save Case"), caseMenu);
    connect(saveCaseAct, SIGNAL(triggered()), caseTreeView, SLOT(saveCase()));
    caseMenu->addAction(newCaseAct);
    caseMenu->addAction(openCaseAct);
    caseMenu->addAction(closeCaseAct);
    caseMenu->addAction(saveCaseAct);

    QAction *scriptExcAct = new QAction(QIcon(":/images/excute.png"), tr("Excute"), scriptMenu);
    connect(scriptExcAct, SIGNAL(triggered()), this, SLOT(scriptExcuteActSlot()));
    scriptMenu->addAction(scriptExcAct);

    QAction *chineseLanAct = new QAction(tr("Chinese"), languageMenu);
    connect(chineseLanAct, SIGNAL(triggered()), this, SLOT(languageChineseActSlot()));
    QAction *englishLanAct = new QAction(tr("English"), languageMenu);
    connect(englishLanAct, SIGNAL(triggered()), this, SLOT(languageEnglishActSlot()));
    languageMenu->addAction(chineseLanAct);
    languageMenu->addAction(englishLanAct);
    QAction *exitAct = new QAction(tr("Exit"), systemMenu);
    connect(exitAct, SIGNAL(triggered()), qApp, SLOT(quit()));
    systemMenu->addAction(exitAct);

    QAction *aboutAct = new QAction(tr("About"), helpMenu);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(helpAboutActSlot()));
    helpMenu->addAction(aboutAct);

    //init menu bar
    QToolBar *mainToolBar = new QToolBar(tr("Tool bar"), this);
    mainToolBar->addAction(newCaseAct);
    mainToolBar->addAction(openCaseAct);
    mainToolBar->addAction(saveCaseAct);
    mainToolBar->addAction(scriptExcAct);
    this->addToolBar(Qt::TopToolBarArea, mainToolBar);

    //init statusBar
    QStatusBar *mainStatusBar = new QStatusBar(this);
    connect(caseTreeView, SIGNAL(message(QString)), mainStatusBar, SLOT(showMessage(QString)));
    this->setStatusBar(mainStatusBar);

    //show maximize
    this->setWindowState(Qt::WindowMaximized);
}
