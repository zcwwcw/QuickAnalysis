#ifndef FINSETTREEITEM_H
#define FINSETTREEITEM_H

#include "treeitem.h"
#include "finsetchildtreeitem.h"

class FinsetTreeItem : public TreeItem
{
public:
    FinsetTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);
};

#endif // FINSETTREEITEM_H
