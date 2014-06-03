#ifndef GEOMETRYTREEITEM_H
#define GEOMETRYTREEITEM_H

#include <QStringList>
#include "treeitem.h"
#include "casecontent.h"

class GeometryTreeItem : public TreeItem
{
public:
    enum TnoseType
    {
        TNOSE_CONICAL,
        TNOSE_OGVIE,
        TNOSE_POWER,
        TNOSE_HAACK,
        TNOSE_KARMAN
    };

    enum TaftType
    {
        TAFT_CONICAL,
        TAFT_OGVIE
    };

    enum EllipseType
    {
        W_H,
        W_ELLIP,
        H_ELLIP
    };

    GeometryTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

    QList<QVariant> getProperty() const;

    void setNewPropertyData(QString objectName, QString value);

    void setNewPropertyCheckState(QString objectName, Qt::CheckState value);
private:
    float m_lonse;
    float m_dnose;

    TnoseType m_tnose;
    float m_power;

    Qt::CheckState m_truncCheck;
    bool m_trunc;
    float m_bnose;

    float m_lcentr;
    float m_decntr;
    float m_laft;
    float m_daft;
    Qt::CheckState m_taftCheck;
    TaftType m_taft;


    float m_dexit;
    bool m_base;

    float m_betan;
    QVariant m_jmach;
    QVariant m_prat;
    QVariant m_trat;

    Qt::CheckState m_xoCheck;
    float m_xo;

    int m_nx;
    float m_x;
    float m_r;
    QVariant m_discon;

    float m_wnose;
    float m_enose;

    float m_wcentr;
    float m_ecentr;
    float m_waft;
    float m_eaft;

    EllipseType m_ellipseType;
    QVariant m_h;
    QVariant m_w;
    QVariant m_ellip;
};

#endif // GEOMETRYTREEITEM_H
