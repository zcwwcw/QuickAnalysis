#ifndef CONTROLTREEITEM_H
#define CONTROLTREEITEM_H

#include "treeitem.h"
#include "casecontent.h"
class ControlTreeItem : public TreeItem
{
public:
    ControlTreeItem(const CaseContent &content, const QList<QVariant> &data, TreeItem *parent = 0);
private:
    CaseContent m_content;
};

#endif // CONTROLTREEITEM_H
