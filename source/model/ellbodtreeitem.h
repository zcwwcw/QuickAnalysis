#ifndef ELLBODTREEITEM_H
#define ELLBODTREEITEM_H

#include "treeitem.h"
#include "casecontent.h"

class EllbodTreeItem : public TreeItem
{
public:
    EllbodTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // ELLBODTREEITEM_H
