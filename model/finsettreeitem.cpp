#include "finsettreeitem.h"

const QLatin1String FINSETKEY("FINSET");

FinsetTreeItem::FinsetTreeItem(const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent)
{
}

void FinsetTreeItem::setContent(const CaseContent &caseContent)
{
    QHash<QString, CaseContent> childContent = caseContent.childContent;
    QStringList keys = childContent.keys();
    for(int i = 0, iend = keys.count(); i < iend; i++)
    {
        if(keys[i].contains(FINSETKEY))
        {
            QString key = keys[i];
            QList<QVariant> finsetChildItemData;
            finsetChildItemData << tr("FINSET") + key[key.size() - 1];
            FinsetChildTreeItem *childItem = new FinsetChildTreeItem(finsetChildItemData, this);
            childItem->setContentKey(key);
            childItem->setContent(caseContent);
            this->appendChild(childItem);
        }
    }
}
