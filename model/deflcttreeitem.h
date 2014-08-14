#ifndef DEFLCTTREEITEM_H
#define DEFLCTTREEITEM_H

#include "treeitem.h"
#include "casecontent.h"

class DeflctTreeItem : public TreeItem
{
public:
    DeflctTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // DEFLCTTREEITEM_H
