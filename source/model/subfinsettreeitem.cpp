#include "subfinsettreeitem.h"

SubFinsetTreeItem::SubFinsetTreeItem(const CaseContent &content, const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent), m_content(content)
{
}
