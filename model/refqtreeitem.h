#ifndef REFQTREEITEM_H
#define REFQTREEITEM_H

#include <QVariant>
#include "propertyconstants.h"
#include "treeitem.h"
#include "casecontent.h"

class RefqTreeItem : public TreeItem
{
    Q_OBJECT
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

    float getXCGValue() const;
private:
    float m_xcg;
    float m_zcg;

    bool m_referenceEnable;
    float m_sref;
    float m_lref;
    float m_latref;

    bool m_blayerEnable;
    BlayerType m_blayer;

    bool m_roughnessEnable;
    CrudeType m_crude;
    float m_rough;
    float m_rhr;

    bool m_scaleEnable;
    float m_scale;
};

#endif // REFQTREEITEM_H
