#ifndef FINSETCHILDTREEITEM_H
#define FINSETCHILDTREEITEM_H

#include "treeitem.h"

class FinsetChildTreeItem : public TreeItem
{
    Q_OBJECT
public:
    enum SECTYPE
    {
        HEX,
        ARC,
        USER,
        NACA
    };

    enum XLETYPE
    {
        XLE,
        XLE_SWEEP
    };

    explicit FinsetChildTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

    void setContentKey(const QString &key);
private:
    QString m_key;
    SECTYPE m_secType;
    QVariant m_sspan;
    QVariant m_chord;
    XLETYPE m_xleType;
    QVariant m_xle;
    float m_xle1;
    QVariant m_sweep;
    QVariant m_sta;
    QVariant m_ler;
    int m_npael;
    QVariant m_phif;
    QVariant m_gam;
    QVariant m_cfoc;
    QVariant m_zupper;
    QVariant m_zlower;
    QVariant m_lmaxu;
    QVariant m_lmaxl;
    QVariant m_lflatu;
    QVariant m_lflatl;
    QVariant m_xcord;
    QVariant m_mean;
    QVariant m_thick;
    QVariant m_yupper;
    QVariant m_ylower;
};

#endif // FINSETCHILDTREEITEM_H
