#ifndef PROTUBTREEITEM_H
#define PROTUBTREEITEM_H

#include "treeitem.h"

class ProtubTreeItem : public TreeItem
{
public:
    ProtubTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // PROTUBTREEITEM_H
