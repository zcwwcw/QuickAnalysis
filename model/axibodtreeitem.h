#ifndef AXIBODTREEITEM_H
#define AXIBODTREEITEM_H

#include "treeitem.h"
#include "casecontent.h"

class AxibodTreeItem : public TreeItem
{
public:
    AxibodTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
};

#endif // AXIBODTREEITEM_H
