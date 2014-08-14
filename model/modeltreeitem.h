#ifndef MODELTREEITEM_H
#define MODELTREEITEM_H

#include "treeitem.h"

class ModelTreeItem : public TreeItem
{
public:
    ModelTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // MODELTREEITEM_H
