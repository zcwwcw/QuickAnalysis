#ifndef REFQTREEITEM_H
#define REFQTREEITEM_H

#include <QVariant>
#include "propertyconstants.h"
#include "treeitem.h"
#include "casecontent.h"

class RefqTreeItem : public TreeItem
{
public:
    enum BlayerType
    {
        TURB,
        NATURAL
    };

    enum CrudeType
    {
        ROUGH,
        RHR
    };

    RefqTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

    QList<QVariant> getProperty() const;

    void setNewPropertyData(QString objectName, QString value);

    void setNewPropertyCheckState(QString objectName, Qt::CheckState value);
private:
    float m_xcg;
    float m_zcg;

    Qt::CheckState m_srefCheck;
    float m_sref;
    Qt::CheckState m_lrefCheck;
    float m_lref;
    Qt::CheckState m_latrefCheck;
    float m_latref;

    Qt::CheckState m_blayerCheck;
    BlayerType m_blayer;

    CrudeType m_crude;
    Qt::CheckState m_roughCheck;
    float m_rough;
    Qt::CheckState m_rhrCheck;
    float m_rhr;

    Qt::CheckState m_scaleCheck;
    float m_scale;
};

#endif // REFQTREEITEM_H
