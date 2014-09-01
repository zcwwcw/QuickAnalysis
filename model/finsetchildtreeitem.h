#ifndef FINSETCHILDTREEITEM_H
#define FINSETCHILDTREEITEM_H

#include "treeitem.h"

class FinsetChildTreeItem : public TreeItem
{
    Q_OBJECT
public:
    explicit FinsetChildTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

};

#endif // FINSETCHILDTREEITEM_H
