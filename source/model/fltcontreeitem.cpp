#include "fltcontreeitem.h"

const QLatin1String FLTCONKEY("FLTCON");
const QLatin1String NALPHAKEY("NALPHA");
const QLatin1String ALPHAKEY("ALPHA");
const QLatin1String BETAKEY("BETA");
const QLatin1String BETACHECKKEY("BETACHECK");
const QLatin1String PHIKEY("PHI");
const QLatin1String PHICHECKKEY("PHICHECK");
const QLatin1String TYPEKEY("TYPE");
const QLatin1String NMACHKEY("NMACH");
const QLatin1String MACHKEY("MACH");
const QLatin1String NVINFKEY("NVINF");
const QLatin1String VINFKEY("VINF");
const QLatin1String REYNOLDSTYPEKEY("REYNOLDSTYPE");
const QLatin1String RENKEY("REN");
const QLatin1String ALTKEY("ALT");
const QLatin1String PINFKEY("PINF");
const QLatin1String TINFKEY("TINF");

const QList<QVariant> TypeList(QList<QVariant>() << QVariant(QObject::tr("MACH")) << QVariant(QObject::tr("VINF")));
const QList<QVariant> ReynoldsList(QList<QVariant>() << QVariant(QObject::tr("REN")) << QVariant(QObject::tr("ALT"))
                                   << QVariant(QObject::tr("PINF+TINF")));

FltconTreeItem::FltconTreeItem(const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent), m_nalpha(2)
    ,m_betaCheckState(Qt::Unchecked), m_beta(0)
    ,m_phiCheckState(Qt::Unchecked), m_phi(0), m_type(MACH), m_nmach(2)
    ,m_nvinf(2), m_reyType(REN)
{
}

void FltconTreeItem::setContent(const CaseContent &caseContent)
{
    QHash<QString, CaseContent>::const_iterator iter;
    for(iter = caseContent.childContent.begin();iter != caseContent.childContent.end(); iter++)
    {
        QHash<QString, CaseContent> childContent = caseContent.childContent;
        if(childContent.find(FLTCONKEY) != childContent.end())
        {
            QHash<QString, CaseContent> fltConContent = childContent.value(FLTCONKEY).childContent;
            //NALPHA
            if(fltConContent.find(NALPHAKEY) != fltConContent.end())
            {
                QString nalphaValue = fltConContent.value(NALPHAKEY).value.toString();
                m_nalpha = nalphaValue.toFloat();
            }
            //ALPHA
            if(fltConContent.find(ALPHAKEY) != fltConContent.end())
            {
                QString alphaValue = fltConContent.value(ALPHAKEY).value.toString();
                QStringList alphaList = alphaValue.split(",");
                QString alphaStr;
                for(int i = 0, iend = alphaList.size(); i < iend; i++)
                {
                    alphaStr = alphaStr + QString::number(alphaList[i].toFloat(), 'f', 0) + ",";
                }
                m_alpha = alphaStr;
            }
            //BETA
            if(fltConContent.find(BETAKEY) != fltConContent.end())
            {
                m_betaCheckState = Qt::Checked;
                QString betaValue = fltConContent.value(BETAKEY).value.toString();
                m_beta = betaValue.toFloat();
            }
            //PHI
            if(fltConContent.find(PHIKEY) != fltConContent.end())
            {
                m_phiCheckState = Qt::Checked;
                QString phiValue = fltConContent.value(PHIKEY).value.toString();
                m_phi = phiValue.toFloat();
            }
            //MACH
            if(fltConContent.find(NMACHKEY) != fltConContent.end() &&
                    fltConContent.find(MACHKEY) != fltConContent.end())
            {
                m_type = MACH;
                QString nmachValue = fltConContent.value(NMACHKEY).value.toString();
                m_nmach = nmachValue.toFloat();
                QString machValue = fltConContent.value(MACHKEY).value.toString();
                QStringList machList = machValue.split(",");
                QString machStr;
                for(int i = 0, iend = machList.size(); i < iend; i++)
                {
                    machStr = machStr + QString::number(machList[i].toFloat(), 'f', 2) + ",";
                }
                m_mach = machStr;
            }
            //VINF
            else if(fltConContent.find(NVINFKEY) != fltConContent.end() &&
                    fltConContent.find(VINFKEY) != fltConContent.end())
            {
                m_type = VINF;
                QString nvinfValue = fltConContent.value(NVINFKEY).value.toString();
                nvinfValue = nvinfValue.toFloat();
                m_nvinf = fltConContent.value(NVINFKEY).value.toFloat();
                QString vinfValue = fltConContent.value(VINFKEY).value.toString();
                QStringList vinfList = vinfValue.split(",");
                QString vinfStr;
                for(int i = 0, iend = vinfList.size(); i < iend; i++)
                {
                    vinfStr = vinfStr + QString::number(vinfList[i].toFloat(), 'f', 2) + ",";
                }
                m_vinf = vinfStr;
            }

            //REN
            if(fltConContent.find(RENKEY) != fltConContent.end())
            {
                m_reyType = REN;
                QString renValue = fltConContent.value(RENKEY).value.toString();
                QStringList renList = renValue.split(",");
                QString renStr;
                for(int i = 0, iend = renList.size(); i < iend; i++)
                {
                    renStr = renStr + QString::number(renList[i].toFloat(), 'f', 2) + ",";
                }
                m_ren = renStr;
            }
            //ALT
            else if(fltConContent.find(ALTKEY) != fltConContent.end())
            {
                m_reyType = ALT;
                QString altValue = fltConContent.value(ALTKEY).value.toString();
                QStringList altList = altValue.split(",");
                QString altStr;
                for(int i = 0, iend = altList.size(); i < iend; i++)
                {
                    altStr = altStr + QString::number(altList[i].toFloat(), 'f', 2) + ",";
                }
                m_alt = altStr;
            }
            else if(fltConContent.find(PINFKEY) != fltConContent.end() &&
                    fltConContent.find(TINFKEY) != fltConContent.end())
            {
                m_reyType = PINF_TINF;
                QString pinfValue = fltConContent.value(PINFKEY).value.toString();
                QStringList pinfList = pinfValue.split(",");
                QString pinfStr;
                for(int i = 0, iend = pinfList.size(); i < iend; i++)
                {
                    pinfStr = pinfStr + QString::number(pinfList[i].toFloat(), 'f', 2) + ",";
                }
                m_pinf = pinfStr;
                QString tinfValue = fltConContent.value(TINFKEY).value.toString();
                QStringList tinfList = tinfValue.split(",");
                QString tinfStr;
                for(int i = 0, iend = tinfList.size(); i < iend; i++)
                {
                    tinfStr = tinfStr + QString::number(tinfList[i].toFloat(), 'f', 2) + ",";
                }
                m_tinf = tinfStr;
            }
        }
    }
}

QList<QVariant> FltconTreeItem::getProperty() const
{
    QList<QVariant> propertyItems;

    //ALPHA
    propertyItems.append(getPropertyItem(NALPHAKEY, tr("NALPHA"),
                                         PROPERTY_TYPE_INT, m_nalpha,
                                         2, 20));
    QString alphaPattern;
    for(int i = 0, iend = m_nalpha; i < iend; i++)
    {
        alphaPattern.append("[-+]?[0-9]\\d{0,1},");
    }
    propertyItems.append(getPropertyItem(ALPHAKEY, tr("ALPHA(deg)"),
                                         PROPERTY_TYPE_STRING_REG, m_alpha,
                                         0, 0, 0, false, Qt::Unchecked, QList<QVariant>(),
                                         true, alphaPattern));
    //BETA
    propertyItems.append(getPropertyItem(BETAKEY, tr("BETA(deg)"),
                                         PROPERTY_TYPE_INT, m_beta, -90, 90, 0,
                                         true, m_betaCheckState));
    //PHI
    propertyItems.append(getPropertyItem(PHIKEY, tr("PHI(deg)"),
                                         PROPERTY_TYPE_INT, m_phi, -90, 90, 0,
                                         true, m_phiCheckState));
    
    int count = 0;
    PropertyItem typeGroupItem = getPropertyItem(TYPEKEY, tr("Type Select"),
                                                 PROPERTY_TYPE_ENUM_GROUP, m_type, 0,
                                                 0, 0, false, Qt::Unchecked, TypeList);
    QList<QVariant> typeChildProperty;
    if(m_type == MACH)
    {
        PropertyItem nmachItem = getPropertyItem(NMACHKEY, tr("NMACH"),
                                                 PROPERTY_TYPE_INT, m_nmach, 2, 20);
        QString machPattern;
        for(int i = 0, iend = m_nmach; i < iend; i++)
        {
            machPattern.append("[0-9]\\d{0,1}.[0-9]\\d{0,1},");
        }
        PropertyItem machValueItem = getPropertyItem(MACHKEY, tr("MACH"),
                                                     PROPERTY_TYPE_STRING_REG, m_mach,
                                                     0, 0, 0, false, Qt::Unchecked,
                                                     QList<QVariant>(), true, machPattern);
        typeChildProperty.append(nmachItem);
        typeChildProperty.append(machValueItem);
        count = m_nmach;
    }
    else if(m_type == VINF)
    {
        PropertyItem nvinfItem = getPropertyItem(NVINFKEY, tr("NVINF"),
                                                 PROPERTY_TYPE_INT, m_nvinf, 2, 20);
        QString vinfPattern;
        for(int i = 0, iend = m_nvinf; i < iend; i++)
        {
            vinfPattern.append("[0-9]\\d{0,1}.[0-9]\\d{0,1},");
        }
        PropertyItem vinfItem = getPropertyItem(VINFKEY, tr("VINF(L/sec)"),
                                                PROPERTY_TYPE_STRING_REG, m_vinf,
                                                0, 0, 0, false, Qt::Unchecked,
                                                QList<QVariant>(), true, vinfPattern);
        typeChildProperty.append(nvinfItem);
        typeChildProperty.append(vinfItem);
        count = m_nvinf;
    }
    typeGroupItem.insert(PropertyConstants::CHILD_PROPERTY, typeChildProperty);
    propertyItems.append(typeGroupItem);

    PropertyItem reyGroupItem = getPropertyItem(REYNOLDSTYPEKEY, QObject::tr("Reynolds Number"),
                                                PROPERTY_TYPE_ENUM_GROUP, m_reyType, 0, 0, 0,
                                                false, Qt::Unchecked, ReynoldsList);
    QList<QVariant> reyChildProperty;
    if(m_reyType == REN)
    {
        QString renPattern;
        for(int i = 0, iend = count; i < iend; i++)
        {
            renPattern.append("\\d+.[0-9]\\d{0,1},");
        }
        PropertyItem renValueItem = getPropertyItem(RENKEY, tr("REN(1/L)"),
                                                    PROPERTY_TYPE_STRING_REG, m_ren,
                                                    0, 0, 0, false, Qt::Unchecked,
                                                    QList<QVariant>(), true, renPattern);
        reyChildProperty.append(renValueItem);
    }
    else if(m_reyType == ALT)
    {
        QString altPattern;
        for(int i = 0, iend = count; i < iend; i++)
        {
            altPattern.append("\\d+.[0-9]\\d{0,1},");
        }
        PropertyItem altValueItem = getPropertyItem(ALTKEY, tr("ALT(L)"),
                                                    PROPERTY_TYPE_STRING_REG, m_alt,
                                                    0, 0, 0, false, Qt::Unchecked,
                                                    QList<QVariant>(), true, altPattern);
        reyChildProperty.append(altValueItem);
    }
    else if(m_reyType == PINF_TINF)
    {
        QString pinf_tinf_Pattern;
        for(int i = 0, iend = count; i < iend; i++)
        {
            pinf_tinf_Pattern.append("\\d+.[0-9]\\d{0,1},");
        }
        PropertyItem pinfValueItem = getPropertyItem(PINFKEY, tr("PINF(L*L)"),
                                                     PROPERTY_TYPE_STRING_REG, m_pinf,
                                                     0, 0, 0, false, Qt::Unchecked,
                                                     QList<QVariant>(), true, pinf_tinf_Pattern);
        PropertyItem tinfValueItem = getPropertyItem(TINFKEY, tr("TINF(deg)"),
                                                     PROPERTY_TYPE_STRING_REG, m_tinf,
                                                     0, 0, 0, false, Qt::Unchecked,
                                                     QList<QVariant>(), true, pinf_tinf_Pattern);
        reyChildProperty.append(pinfValueItem);
        reyChildProperty.append(tinfValueItem);
    }
    reyGroupItem.insert(PropertyConstants::CHILD_PROPERTY, reyChildProperty);
    propertyItems.append(reyGroupItem);

    return propertyItems;
}

void FltconTreeItem::setNewPropertyData(QString objectName, QString value)
{
    if(objectName == NALPHAKEY)
    {
        m_nalpha = value.toInt();
        m_alpha = setNewContent(m_alpha, m_nalpha, "0,");
        emit propertiesUpdate();
    }
    else if(objectName == ALPHAKEY)
    {
        m_alpha = value;
    }
    else if(objectName == BETAKEY)
    {
        m_beta = value.toInt();
    }
    else if(objectName == PHIKEY)
    {
        m_phi = value.toInt();
    }
    else if(objectName == TYPEKEY)
    {
        m_type = (TYPE)TypeList.indexOf(value);
        int reyCount = 0;
        if(m_type == MACH)
        {
            m_mach = setNewContent(m_mach, m_nmach, "1.00,");
            reyCount = m_nmach;
        }
        else if(m_type == VINF)
        {
            m_vinf = setNewContent(m_vinf, m_nvinf, "1.00,");
            reyCount = m_nvinf;
        }

        if(m_reyType == REN)
        {
            m_ren = setNewContent(m_ren, reyCount, "0.00,");
        }
        else if(m_reyType == ALT)
        {
            m_alt = setNewContent(m_alt, reyCount, "0.00,");
        }
        else if(m_reyType == PINF_TINF)
        {
            m_pinf = setNewContent(m_pinf, reyCount, "0.00,");
            m_tinf = setNewContent(m_tinf, reyCount, "0.00,");
        }
        emit propertiesRebuild();
    }
    else if(objectName == NMACHKEY)
    {
        m_nmach = value.toInt();
        m_mach = setNewContent(m_mach, m_nmach, "1.00,");
        int reyCount = m_nmach;
        if(m_reyType == REN)
        {
            m_ren = setNewContent(m_ren, reyCount, "0.00,");
        }
        else if(m_reyType == ALT)
        {
            m_alt = setNewContent(m_alt, reyCount, "0.00,");
        }
        else if(m_reyType == PINF_TINF)
        {
            m_pinf = setNewContent(m_pinf, reyCount, "0.00,");
            m_tinf = setNewContent(m_tinf, reyCount, "0.00,");
        }
        emit propertiesUpdate();
    }
    else if(objectName == MACHKEY)
    {
        m_mach = value;
    }
    else if(objectName == NVINFKEY)
    {
        m_nvinf = value.toInt();
        m_vinf = setNewContent(m_vinf, m_nvinf, "1.00,");
        int reyCount = m_nvinf;
        if(m_reyType == REN)
        {
            m_ren = setNewContent(m_ren, reyCount, "0.00,");
        }
        else if(m_reyType == ALT)
        {
            m_alt = setNewContent(m_alt, reyCount, "0.00,");
        }
        else if(m_reyType == PINF_TINF)
        {
            m_pinf = setNewContent(m_pinf, reyCount, "0.00,");
            m_tinf = setNewContent(m_tinf, reyCount, "0.00,");
        }
        emit propertiesUpdate();
    }
    else if(objectName == VINFKEY)
    {
        m_vinf = value;
    }
    else if(objectName == REYNOLDSTYPEKEY)
    {
        m_reyType = ReynoldsType(ReynoldsList.indexOf(value));
        int reyCount = 0;
        if(m_type == MACH)
        {
            reyCount = m_nmach;
        }
        else if(m_type == VINF)
        {
            reyCount = m_nvinf;
        }
        if(m_reyType == REN)
        {
            m_ren = setNewContent(m_ren, reyCount, "0.00,");
        }
        else if(m_reyType == ALT)
        {
            m_alt = setNewContent(m_alt, reyCount, "0.00,");
        }
        else if(m_reyType == PINF_TINF)
        {
            m_pinf = setNewContent(m_pinf, reyCount, "0.00,");
            m_tinf = setNewContent(m_tinf, reyCount, "0.00,");
        }
        emit propertiesRebuild();
    }
    else if(objectName == RENKEY)
    {
        m_ren = value;
    }
    else if(objectName == ALTKEY)
    {
        m_alt = value;
    }
    else if(objectName == PINFKEY)
    {
        m_pinf = value;
    }
    else if(objectName == TINFKEY)
    {
        m_tinf = value;
    }
}

void FltconTreeItem::setNewPropertyCheckState(QString objectName, Qt::CheckState value)
{
    if(objectName == BETAKEY)
    {
        m_betaCheckState = value;
    }
    else if(objectName == PHIKEY)
    {
        m_phiCheckState = value;
    }
}

QVariant FltconTreeItem::setNewContent(QVariant oriData, int setCount, QString appendStr)
{
    QVariant newData = oriData;
    QString oriStr = oriData.toString();
    QStringList oriList = oriStr.split(",", QString::SkipEmptyParts);
    int valueCount = oriList.size();
    if(setCount > valueCount)
    {
        for(int i = 0, iend = setCount - valueCount; i < iend; i++)
        {
            oriStr.append(appendStr);
        }
        newData = oriStr;
    }
    else if(setCount < valueCount)
    {
        oriStr.clear();
        for(int i = 0, iend = setCount; i < iend; i++)
        {
            oriStr = oriStr + oriList[i] + ",";
        }
        newData = oriStr;
    }
    return newData;
}
