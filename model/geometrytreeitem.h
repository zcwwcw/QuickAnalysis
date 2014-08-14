#ifndef GEOMETRYTREEITEM_H
#define GEOMETRYTREEITEM_H

#include <QStringList>
#include "treeitem.h"
#include "casecontent.h"
#include "propertyconstants.h"

class GeometryTreeItem : public TreeItem
{
    Q_OBJECT
public:
    enum TnoseType
    {
        TNOSE_CONICAL,
        TNOSE_OGVIE,
        TNOSE_POWER,
        TNOSE_HAACK,
        TNOSE_KARMAN
    };

    enum HeadType
    {
        PASSIVATE,
        TRUNCATE
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

    enum GeometryType
    {
        AXIBOD,
        AXIBOD_NX,
        ELLBOD,
        ELLBOD_NX
    };

    GeometryTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

    QList<QVariant> getProperty() const;

    void setNewPropertyData(QString objectName, QString value);

    void setNewPropertyCheckState(QString objectName, Qt::CheckState value);
public slots:
    void nmachOrnvinfChanged();
private:
    float m_lnose;
    float m_dnose;

    TnoseType m_tnose;
    float m_power;

    HeadType m_headType;
    float m_bnose;

    float m_lcentr;
    float m_dcentr;
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
    QVariant m_x;
    QVariant m_r;
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

    GeometryType m_type;
};

#endif // GEOMETRYTREEITEM_H
