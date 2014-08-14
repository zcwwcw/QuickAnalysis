#ifndef FINSETTREEITEM_H
#define FINSETTREEITEM_H

#include "treeitem.h"

class FinsetTreeItem : public TreeItem
{
public:
    FinsetTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // FINSETTREEITEM_H
