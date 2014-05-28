#ifndef TRIMTREEITEM_H
#define TRIMTREEITEM_H

#include "treeitem.h"

class TrimTreeItem : public TreeItem
{
public:
    TrimTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // TRIMTREEITEM_H
