#include "protubtreeitem.h"

const QLatin1String PROTUBKEY("PROTUB");
const QLatin1String NPROTKEY("NPROT");
const QLatin1String PTYPEKEY("PTYPE");
const QLatin1String XPROTKEY("XPROT");
const QLatin1String NLOCKEY("NLOC");
const QLatin1String LPROTKEY("LPROT");
const QLatin1String WPROTKEY("WPROT");
const QLatin1String HPROTKEY("HPROT");
const QLatin1String OPROTKEY("OPROT");

const QList<QVariant> PtypeList(QList<QVariant>()
                                << QVariant(QObject::tr("VCYL"))
                                << QVariant(QObject::tr("HCYL"))
                                << QVariant(QObject::tr("BLOCK"))
                                << QVariant(QObject::tr("FAIRING"))
                                << QVariant(QObject::tr("LUG"))
                                << QVariant(QObject::tr("SHOE"))
                                );

ProtubTreeItem::ProtubTreeItem(const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent),m_nprot(0)
{
}

void ProtubTreeItem::setContent(const CaseContent &caseContent)
{
    QHash<QString, CaseContent> childContent = caseContent.childContent;
    if(childContent.find(PROTUBKEY) != childContent.end())
    {
        QHash<QString, CaseContent> protubContent = childContent.value(PROTUBKEY).childContent;
        //NPROT
        if(protubContent.find(NPROTKEY) != protubContent.end())
        {
            QString nprotValue = protubContent.value(NPROTKEY).value.toString();
            m_nprot = nprotValue.toFloat();
        }
        //PTYPE
        if(protubContent.find(PTYPEKEY) != protubContent.end())
        {
            QString ptypeValue = protubContent.value(PTYPEKEY).value.toString();
            QStringList ptypeValues = ptypeValue.split(",");
            for(int i = 0, iend = ptypeValues.size(); i < iend; i++)
            {
                PTYPE ptype = getPtypeValue(ptypeValues[i]);
                m_ptype.append(ptype);
            }
        }
        //XPROT
        if(protubContent.find(XPROTKEY) != protubContent.end())
        {
            QString xprotValue = protubContent.value(XPROTKEY).value.toString();
            QStringList xprotList = xprotValue.split(",");
            QString xprotStr;
            for(int i = 0, iend = xprotList.size(); i < iend; i++)
            {
                xprotStr = xprotStr + QString::number(xprotList[i].toFloat(), 'f', 0) + ",";
            }
            m_xprot = xprotStr;
        }
        //NLOC
        if(protubContent.find(NLOCKEY) != protubContent.end())
        {
            QString nlocValue = protubContent.value(NLOCKEY).value.toString();
            QStringList nlocList = nlocValue.split(",");
            QString nlocStr;
            for(int i = 0, iend = nlocList.size(); i < iend; i++)
            {
                nlocStr = nlocStr + QString::number(nlocList[i].toFloat(), 'f', 0) + ",";
            }
            m_nloc = nlocStr;
        }
        //LPROT
        if(protubContent.find(LPROTKEY) != protubContent.end())
        {
            QString lprotValue = protubContent.value(LPROTKEY).value.toString();
            m_lprot = lprotValue;
        }
        //WPROT
        if(protubContent.find(WPROTKEY) != protubContent.end())
        {
            QString wprotValue = protubContent.value(WPROTKEY).value.toString();
            m_wprot = wprotValue;
        }
        //HPROT
        if(protubContent.find(HPROTKEY) != protubContent.end())
        {
            QString hprotValue = protubContent.value(HPROTKEY).value.toString();
            m_hprot = hprotValue;
        }
        //OPROT
        if(protubContent.find(OPROTKEY) != protubContent.end())
        {
            QString oprotValue = protubContent.value(OPROTKEY).value.toString();
            m_oprot = oprotValue;
        }
    }
}

QList<QVariant> ProtubTreeItem::getProperty() const
{
    QList<QVariant> propertyItems;
    //NPROT
    propertyItems.append(getPropertyItem(NPROTKEY, tr("NPROT"),
                                         PROPERTY_TYPE_INT, m_nprot,
                                         0, 20));
    //PTYPE
    PropertyItem ptypeGroupItem = getPropertyItem(PTYPEKEY, tr("PTYPE"),
                                                 PROPERTY_TYPE_GROUP);
    QList<QVariant> ptypeChildProperty;
    for(int i = 0, iend = m_ptype.size(); i < iend; i++)
    {
        PropertyItem ptypeChildItem = getPropertyItem(PTYPEKEY + QString::number(i),
                                                      tr("PTYPE_") + QString::number(i),
                                                      PROPERTY_TYPE_ENUM, m_ptype[i],
                                                      0, 0, 0,
                                                      false, Qt::Unchecked,
                                                      PtypeList);
        ptypeChildProperty.append(ptypeChildItem);
    }
    ptypeGroupItem.insert(PropertyConstants::CHILD_PROPERTY, ptypeChildProperty);
    propertyItems.append(ptypeGroupItem);
    //XPROT
    PropertyItem xprotItem = getPropertyItem(XPROTKEY, tr("XPROT"),
                                             PROPERTY_TYPE_STRING, m_xprot);
    propertyItems.append(xprotItem);
    //NLOC
    PropertyItem nlocItem = getPropertyItem(NLOCKEY, tr("NLOC"),
                                            PROPERTY_TYPE_STRING, m_nloc);
    propertyItems.append(nlocItem);
    //LPROT
    PropertyItem lprotItem = getPropertyItem(LPROTKEY, tr("LPROT"),
                                            PROPERTY_TYPE_STRING, m_lprot);
    propertyItems.append(lprotItem);
    //WPROT
    PropertyItem wprotItem = getPropertyItem(WPROTKEY, tr("WPROT"),
                                            PROPERTY_TYPE_STRING, m_wprot);
    propertyItems.append(wprotItem);
    //HPROT
    PropertyItem hprotItem = getPropertyItem(HPROTKEY, tr("HPROT"),
                                            PROPERTY_TYPE_STRING, m_hprot);
    propertyItems.append(hprotItem);
    //OPROT
    PropertyItem oprotItem = getPropertyItem(OPROTKEY, tr("OPROT"),
                                            PROPERTY_TYPE_STRING, m_oprot);
    propertyItems.append(oprotItem);
    return propertyItems;
}

void ProtubTreeItem::setNewPropertyData(QString objectName, QString value)
{
    if(objectName == NPROTKEY)
    {
        m_nprot = value.toInt();
    }
    else if(objectName.contains(PTYPEKEY))
    {
        const int index = objectName.remove(PTYPEKEY).toInt();
        if(index >= 0 && index < m_ptype.size())
        {
            m_ptype[index] = (PTYPE)value.toInt();
        }
    }
    else if(objectName == XPROTKEY)
    {
        m_xprot = value;
    }
    else if(objectName == NLOCKEY)
    {
        m_nloc = value;
    }
    else if(objectName == LPROTKEY)
    {
        m_lprot = value;
    }
    else if(objectName == WPROTKEY)
    {
        m_wprot = value;
    }
    else if(objectName == HPROTKEY)
    {
        m_hprot = value;
    }
    else if(objectName == OPROTKEY)
    {
        m_oprot = value;
    }
}

ProtubTreeItem::PTYPE ProtubTreeItem::getPtypeValue(const QString &value)
{
    PTYPE type = VCYL;
    if(value == "VCYL")
    {
        type = VCYL;
    }
    else if(value == "HCYL")
    {
        type = HCYL;
    }
    else if(value == "BLOCK")
    {
        type = BLOCK;
    }
    else if(value == "FAIRING")
    {
        type = FAIRING;
    }
    else if(value == "LUG")
    {
        type = LUG;
    }
    else if(value == "SHOE")
    {
        type = SHOE;
    }
    return type;
}
