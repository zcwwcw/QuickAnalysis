#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QObject>
#include "casecontent.h"
#include "model_global.h"

class MODELSHARED_EXPORT TreeItem : public QObject
{
    Q_OBJECT
public:
    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    virtual ~TreeItem();

    void appendChild(TreeItem *child);

    TreeItem *child(int row);
    int indexOfItem(TreeItem *item) const;
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem *parent();

    virtual void setContent(const CaseContent &caseContent);

    virtual QList<QVariant> getProperty() const;

    virtual void setNewPropertyData(QString objectName, QString value);

    virtual void setNewPropertyCheckState(QString objectName, Qt::CheckState value);
signals:
    void propertiesUpdate();

    void propertiesRebuild();
private:
    QList<TreeItem*> m_childItems;
    QList<QVariant> m_itemData;
    TreeItem *m_parentItem;
};

#endif // TREEITEM_H
