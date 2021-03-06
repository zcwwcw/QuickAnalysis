#include "fltcontreeitem.h"

const QLatin1String ANGLEKEY("ANGLE");
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
    messageBox.setWindowTitle(tr("Warning"));
}

void FltconTreeItem::setContent(const CaseContent &caseContent)
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

QList<QVariant> FltconTreeItem::getProperty() const
{
    QList<QVariant> propertyItems;

    //ANGLE GROUP
    PropertyItem angleGroupItem = getPropertyItem(ANGLEKEY, tr("ANGLE"),
                                                  PROPERTY_TYPE_GROUP);
    QList<QVariant> angleChildProperty;
    //ALPHA
    angleChildProperty.append(getPropertyItem(NALPHAKEY, tr("NALPHA"),
                                         PROPERTY_TYPE_INT, m_nalpha,
                                         2, 20));
    angleChildProperty.append(getPropertyItem(ALPHAKEY, tr("ALPHA(deg)"),
                                         PROPERTY_TYPE_STRING, m_alpha));
    //BETA
    angleChildProperty.append(getPropertyItem(BETAKEY, tr("BETA(deg)"),
                                         PROPERTY_TYPE_INT, m_beta, -90, 90, 0,
                                         true, m_betaCheckState));
    //PHI
    angleChildProperty.append(getPropertyItem(PHIKEY, tr("PHI(deg)"),
                                         PROPERTY_TYPE_INT, m_phi, -90, 90, 0,
                                         true, m_phiCheckState));
    angleGroupItem.insert(PropertyConstants::CHILD_PROPERTY, angleChildProperty);
    propertyItems.append(angleGroupItem);
    
    //MACH GROUP OR VINF GROUP
    PropertyItem typeGroupItem = getPropertyItem(TYPEKEY, tr("Type Select"),
                                                 PROPERTY_TYPE_ENUM_GROUP, m_type, 0,
                                                 0, 0, false, Qt::Unchecked, TypeList);
    QList<QVariant> typeChildProperty;
    if(m_type == MACH)
    {
        PropertyItem nmachItem = getPropertyItem(NMACHKEY, tr("NMACH"),
                                                 PROPERTY_TYPE_INT, m_nmach, 2, 20);
        PropertyItem machValueItem = getPropertyItem(MACHKEY, tr("MACH"),
                                                     PROPERTY_TYPE_STRING, m_mach);
        typeChildProperty.append(nmachItem);
        typeChildProperty.append(machValueItem);
    }
    else if(m_type == VINF)
    {
        PropertyItem nvinfItem = getPropertyItem(NVINFKEY, tr("NVINF"),
                                                 PROPERTY_TYPE_INT, m_nvinf, 2, 20);
        PropertyItem vinfItem = getPropertyItem(VINFKEY, tr("VINF(L/sec)"),
                                                PROPERTY_TYPE_STRING, m_vinf);
        typeChildProperty.append(nvinfItem);
        typeChildProperty.append(vinfItem);
    }
    typeGroupItem.insert(PropertyConstants::CHILD_PROPERTY, typeChildProperty);
    propertyItems.append(typeGroupItem);

    //REY NUMBER GROUP
    PropertyItem reyGroupItem = getPropertyItem(REYNOLDSTYPEKEY, QObject::tr("Reynolds Number"),
                                                PROPERTY_TYPE_ENUM_GROUP, m_reyType, 0, 0, 0,
                                                false, Qt::Unchecked, ReynoldsList);
    QList<QVariant> reyChildProperty;
    if(m_reyType == REN)
    {
        PropertyItem renValueItem = getPropertyItem(RENKEY, tr("REN(1/L)"),
                                                    PROPERTY_TYPE_STRING, m_ren);
        reyChildProperty.append(renValueItem);
    }
    else if(m_reyType == ALT)
    {
        PropertyItem altValueItem = getPropertyItem(ALTKEY, tr("ALT(L)"),
                                                    PROPERTY_TYPE_STRING, m_alt);
        reyChildProperty.append(altValueItem);
    }
    else if(m_reyType == PINF_TINF)
    {
        PropertyItem pinfValueItem = getPropertyItem(PINFKEY, tr("PINF(L*L)"),
                                                     PROPERTY_TYPE_STRING, m_pinf);
        PropertyItem tinfValueItem = getPropertyItem(TINFKEY, tr("TINF(deg)"),
                                                     PROPERTY_TYPE_STRING, m_tinf);
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
        if(checkStringContent(value, m_nalpha))
        {
            QVariant correctValue = correctStringContent(value, 0);
            m_alpha = correctValue;
        }
        else
        {
            m_alpha = value;
            messageBox.show();
            messageBox.setText(tr("Please check alpha value, like \"1,2,3,4,5,....\" and count equal nalpha value."));
        }
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
        emit nmachChanged();
    }
    else if(objectName == MACHKEY)
    {
        if(checkStringContent(value, m_nmach))
        {
            QVariant correctValue = correctStringContent(value, 2);
            m_mach = correctValue;
        }
        else
        {
            m_mach = value;
            messageBox.show();
            messageBox.setText(tr("Please check mach value, like \"1.00,2.00,3.00,4.00,5.00,....\" and count equal nmach value."));
        }
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
        emit nvinfChanged();
    }
    else if(objectName == VINFKEY)
    {
        if(checkStringContent(value, m_nvinf))
        {
            QVariant correctValue = correctStringContent(value, 2);
            m_vinf = correctValue;
        }
        else
        {
            m_vinf = value;
            messageBox.show();
            messageBox.setText(tr("Please check vinf value, like \"1.00,2.00,3.00,4.00,5.00,....\" and count equal nvinf value."));
        }
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
        int reyCount = 0;
        if(m_type == MACH)
        {
            reyCount = m_nmach;
        }
        else if(m_type == VINF)
        {
            reyCount = m_nvinf;
        }
        if(checkStringContent(value, reyCount))
        {
            QVariant correctValue = correctStringContent(value, 2);
            m_ren = correctValue;
        }
        else
        {
            m_ren = value;
            messageBox.show();
            messageBox.setText(tr("Please check ren value, like \"1.00,2.00,3.00,4.00,5.00,....\" and count equal nmach or nvinf value."));
        }
    }
    else if(objectName == ALTKEY)
    {
        int reyCount = 0;
        if(m_type == MACH)
        {
            reyCount = m_nmach;
        }
        else if(m_type == VINF)
        {
            reyCount = m_nvinf;
        }
        if(checkStringContent(value, reyCount))
        {
            QVariant correctValue = correctStringContent(value, 2);
            m_alt = correctValue;
        }
        else
        {
            m_alt = value;
            messageBox.show();
            messageBox.setText(tr("Please check alt value, like \"1.00,2.00,3.00,4.00,5.00,....\" and count equal nmach or nvinf value."));
        }
    }
    else if(objectName == PINFKEY)
    {
        int reyCount = 0;
        if(m_type == MACH)
        {
            reyCount = m_nmach;
        }
        else if(m_type == VINF)
        {
            reyCount = m_nvinf;
        }
        if(checkStringContent(value, reyCount))
        {
            QVariant correctValue = correctStringContent(value, 2);
            m_pinf = correctValue;
        }
        else
        {
            m_pinf = value;
            messageBox.show();
            messageBox.setText(tr("Please check pinf value, like \"1.00,2.00,3.00,4.00,5.00,....\" and count equal nmach or nvinf value."));
        }
    }
    else if(objectName == TINFKEY)
    {
        int reyCount = 0;
        if(m_type == MACH)
        {
            reyCount = m_nmach;
        }
        else if(m_type == VINF)
        {
            reyCount = m_nvinf;
        }
        if(checkStringContent(value, reyCount))
        {
            QVariant correctValue = correctStringContent(value, 2);
            m_tinf = correctValue;
        }
        else
        {
            m_tinf = value;
            messageBox.show();
            messageBox.setText(tr("Please check tinf value, like \"1.00,2.00,3.00,4.00,5.00,....\" and count equal nmach or nvinf value."));
        }
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

int FltconTreeItem::getNamchOrNvinf() const
{
    int count = 0;
    if(m_type == MACH)
    {
        count = m_nmach;
    }
    else if(m_type == VINF)
    {
        count = m_nvinf;
    }
    return count;
}
