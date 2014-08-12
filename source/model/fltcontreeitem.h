#ifndef FLTCONTREEITEM_H
#define FLTCONTREEITEM_H

#include <QMessageBox>
#include <QStringList>
#include <QHash>
#include <QVariant>
#include <QString>
#include "treeitem.h"
#include "casecontent.h"
#include "propertyconstants.h"

class FltconTreeItem : public TreeItem
{
    Q_OBJECT
public:
    enum TYPE
    {
        MACH,
        VINF
    };

    enum ReynoldsType
    {
        REN,
        ALT,
        PINF_TINF
    };

    FltconTreeItem(const QList<QVariant> &data, TreeItem *parent = 0);

    void setContent(const CaseContent &caseContent);

    QList<QVariant> getProperty() const;

    void setNewPropertyData(QString objectName, QString value);

    void setNewPropertyCheckState(QString objectName, Qt::CheckState value);

    int getNamchOrNvinf() const;
signals:
    void nmachChanged();

    void nvinfChanged();
private:
    int m_nalpha;
    QVariant m_alpha;
    Qt::CheckState m_betaCheckState;
    int m_beta;
    Qt::CheckState m_phiCheckState;
    int m_phi;

    TYPE m_type;
    int m_nmach;
    QVariant m_mach;
    int m_nvinf;
    QVariant m_vinf;

    ReynoldsType m_reyType;
    QVariant m_alt;
    QVariant m_ren;
    QVariant m_tinf;
    QVariant m_pinf;
    QMessageBox messageBox;
};

#endif // FLTCONTREEITEM_H
