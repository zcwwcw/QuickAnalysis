#ifndef INLETTREEITEM_H
#define INLETTREEITEM_H

#include "treeitem.h"
class InletTreeItem : public TreeItem
{
public:
    InletTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // INLETTREEITEM_H
