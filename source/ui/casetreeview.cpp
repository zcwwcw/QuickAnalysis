#include "casetreeview.h"

CaseTreeView::CaseTreeView(QWidget *parent) :
    QTreeView(parent)
{
    m_model = new CaseTreeModel(this);
    connect(m_model, SIGNAL(itemPropertiesUpdate(QObject*)),
            this, SLOT(updateTreeItem(QObject*)));
    connect(m_model, SIGNAL(itemPropertiesRebuild(QObject*)),
            this, SLOT(rebuildTreeItem(QObject*)));
    setModel(m_model);
    initUI();
}

void CaseTreeView::openCase()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Case"), QApplication::applicationDirPath(),
                                                tr("Dat File (*.dat)"));
    if(!path.isEmpty())
    {
        TreeItem *item = m_model->addCase(path);
        if(item)
        {
            reset();
            QModelIndex index = m_model->indexFromItem(item);
            expand(index);
            emit message(tr("Add %1 success!").arg(path));
        }
        else
        {
            emit message(tr("Add %1 fail!").arg(path));
        }
    }
}

void CaseTreeView::createCase()
{

}

void CaseTreeView::closeCase()
{

}

void CaseTreeView::saveCase()
{

}

void CaseTreeView::newPropertyData(QString objectName, QString value)
{
    QModelIndex index = currentIndex();
    if(index.isValid())
    {
        TreeItem *item = m_model->getItem(index);
        item->setNewPropertyData(objectName, value);
    }
}

void CaseTreeView::newPropertyCheckState(QString objectName, Qt::CheckState value)
{
    QModelIndex index = currentIndex();
    if(index.isValid())
    {
        TreeItem *item = m_model->getItem(index);
        item->setNewPropertyCheckState(objectName, value);
    }
}

void CaseTreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if(!index.isValid())
    {
        treeMenu.exec(QCursor::pos());
    }
}

void CaseTreeView::mousePressEvent(QMouseEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if(index.isValid() && m_model->getItem(index))
    {
        TreeItem *item = m_model->getItem(index);
        QList<QVariant> properties = item->getProperty();
        emit showItemProperties(item->data(0).toString(), properties);
    }
    QTreeView::mousePressEvent(event);
}

void CaseTreeView::updateTreeItem(QObject *sourceItem)
{
    QModelIndex index = currentIndex();
    if(index.isValid())
    {
        TreeItem *item = m_model->getItem(index);
        if(item == sourceItem)
        {
            QList<QVariant> properties = item->getProperty();
            emit updateItemProperties(item->data(0).toString(), properties);
        }
    }
}

void CaseTreeView::rebuildTreeItem(QObject *sourceItem)
{
    QModelIndex index = currentIndex();
    if(index.isValid())
    {
        TreeItem *item = m_model->getItem(index);
        if(item == sourceItem)
        {
            QList<QVariant> properties = item->getProperty();
            emit showItemProperties(item->data(0).toString(), properties);
        }
    }
}

void CaseTreeView::initUI()
{
    setHeaderHidden(true);
    QAction *openAct = new QAction(tr("Open"), this);
    QAction *newAct = new QAction(tr("New"), this);
    QAction *collapseAllAct = new QAction(tr("Collapse ALL"), this);
    QAction *expandAllAct = new QAction(tr("Expand All"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openCase()));
    connect(newAct, SIGNAL(triggered()), this, SLOT(createCase()));
    connect(collapseAllAct, SIGNAL(triggered()), this, SLOT(collapseAll()));
    connect(expandAllAct, SIGNAL(triggered()), this, SLOT(expandAll()));
    treeMenu.addAction(openAct);
    treeMenu.addAction(newAct);
    treeMenu.addAction(collapseAllAct);
    treeMenu.addAction(expandAllAct);
}
