#ifndef SOLUTIONTREEITEM_H
#define SOLUTIONTREEITEM_H

#include "treeitem.h"

class SolutionTreeItem : public TreeItem
{
public:
    SolutionTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // SOLUTIONTREEITEM_H
