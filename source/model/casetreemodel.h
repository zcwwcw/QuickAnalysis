#ifndef CASETREEMODEL_H
#define CASETREEMODEL_H

#include <QAbstractItemModel>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>
#include <QSignalMapper>
#include "treeitem.h"
#include "modeltreeitem.h"
#include "solutiontreeitem.h"
#include "casecontent.h"
#include "fltcontreeitem.h"
#include "refqtreeitem.h"
#include "geometrytreeitem.h"
#include "protubtreeitem.h"
#include "finsettreeitem.h"
#include "deflcttreeitem.h"
#include "trimtreeitem.h"
#include "inlettreeitem.h"
#include "model_global.h"

class MODELSHARED_EXPORT CaseTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit CaseTreeModel(QObject *parent = 0);
    ~CaseTreeModel();

    TreeItem *addCase(const QString &filePath);
    TreeItem *getItem(const QModelIndex &index) const;

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex indexFromItem(TreeItem *item, int column = 0) const;
    QModelIndex parent(const QModelIndex &index) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
signals:
    void itemPropertiesUpdate(QObject *updateItem);

    void itemPropertiesRebuild(QObject *updateItem);
private:
    TreeItem *setupModelData(const QString &filePath, TreeItem *parent);

    CaseContent getContent(const QString &tmpData);
private:
    TreeItem * m_rootItem;
    QSignalMapper *m_itemMapper1;
    QSignalMapper *m_itemMapper2;
};

#endif // CASETREEMODEL_H
