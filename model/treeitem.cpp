#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
    : QObject(parent), m_parentItem(parent), m_itemData(data),
      m_itemMapper1(NULL), m_itemMapper2(NULL)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *child)
{
    m_childItems.append(child);
}

QVariant TreeItem::data(int column) const
{
    return m_itemData.value(column);
}

int TreeItem::row() const
{
    if (m_parentItem)
        return m_parentItem->m_childItems.indexOf(const_cast<TreeItem*>(this));
    return 0;
}

TreeItem *TreeItem::parent()
{
    return m_parentItem;
}

void TreeItem::setPropertiesSingalMapper(QSignalMapper *itemMapper1, QSignalMapper *itemMapper2)
{
    m_itemMapper1 = itemMapper1;
    m_itemMapper2 = itemMapper2;
    connect(this, SIGNAL(propertiesUpdate()), m_itemMapper1, SLOT(map()));
    connect(this, SIGNAL(propertiesRebuild()), m_itemMapper2, SLOT(map()));
    m_itemMapper1->setMapping(this, this);
    m_itemMapper2->setMapping(this, this);
}

void TreeItem::setContent(const CaseContent &caseContent)
{
    Q_UNUSED(caseContent)
}

QList<QVariant> TreeItem::getProperty() const
{
    return QList<QVariant>();
}

void TreeItem::setNewPropertyData(QString objectName, QString value)
{
    Q_UNUSED(objectName)
    Q_UNUSED(value)
}

void TreeItem::setNewPropertyCheckState(QString objectName, Qt::CheckState value)
{
    Q_UNUSED(objectName)
    Q_UNUSED(value)
}

TreeItem *TreeItem::child(int row)
{
    return m_childItems.value(row);
}

int TreeItem::indexOfItem(TreeItem *item) const
{
    return m_childItems.indexOf(item);
}

int TreeItem::childCount() const
{
    return m_childItems.count();
}

int TreeItem::columnCount() const
{
    if(m_itemData.count() == 0)
    {
        return 1;
    }
    return m_itemData.count();
}
