#ifndef CASETREEVIEW_H
#define CASETREEVIEW_H

#include <QTreeView>
#include <QFileDialog>
#include <QApplication>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include "casetreemodel.h"

class CaseTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit CaseTreeView(QWidget *parent = 0);
public slots:
    void openCase();

    void createCase();

    void closeCase();

    void saveCase();

    void newPropertyData(QString objectName, QString value);

    void newPropertyCheckState(QString objectName, Qt::CheckState value);
signals:
    void showItemProperties(QString objectName, QList<QVariant> properties);

    void updateItemProperties(QString objectName, QList<QVariant> properties);

    void message(QString message);
protected:
    void contextMenuEvent(QContextMenuEvent *event);

    void mousePressEvent(QMouseEvent *event);
private slots:
    void updateTreeItem(QObject *sourceItem);

    void rebuildTreeItem(QObject *sourceItem);
private:
    void initUI();
private:
    CaseTreeModel *m_model;
    QMenu treeMenu;
};

#endif // CASETREEVIEW_H
