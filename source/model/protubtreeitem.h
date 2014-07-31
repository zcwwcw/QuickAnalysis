#ifndef PROTUBTREEITEM_H
#define PROTUBTREEITEM_H

#include "treeitem.h"
#include <QHash>
#include <QVariant>
#include <QStringList>
#include "propertyconstants.h"

class ProtubTreeItem : public TreeItem
{
    Q_OBJECT
public:
    enum PTYPE
    {
        VCYL,
        HCYL,
        BLOCK,
        FAIRING,
        LUG,
        SHOE
    };

    ProtubTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

    QList<QVariant> getProperty() const;

    void setNewPropertyData(QString objectName, QString value);
private:
    PTYPE getPtypeValue(const QString &value);
private:
    int m_nprot;
    QList<PTYPE> m_ptype;
    QString m_xprot;
    QString m_nloc;
    QString m_lprot;
    QString m_wprot;
    QString m_hprot;
    QString m_oprot;
};

#endif // PROTUBTREEITEM_H
