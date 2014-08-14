#include "refqtreeitem.h"

const QLatin1String LOCATIONOFPRESSUREKEY("LOCATIONOFPRESSURE");
const QLatin1String REFQKEY("REFQ");
const QLatin1String XCGKEY("XCG");
const QLatin1String ZCGKEY("ZCG");
const QLatin1String REFERENCEQUANTITYKEY("REFERENCEQUANTITY");
const QLatin1String SREFKEY("SREF");
const QLatin1String LREFKEY("LREF");
const QLatin1String LATREFKEY("LATREF");
const QLatin1String BOUNDARYLAYERTYPEKEY("BOUNDARYLAYERTYPE");
const QLatin1String BLAYERKEY("BLAYER");
const QLatin1String ROUGHNESSKEY("ROUGHNESS");
const QLatin1String ROUGHKEY("ROUGH");
const QLatin1String RHRKEY("RHR");
const QLatin1String SCALEFACTORKEY("SCALEFACTOR");
const QLatin1String SCALEKEY("SCALE");
const QLatin1String CRUDEKEY("CRUDE");

const QList<QVariant> BlayerList(QList<QVariant>() << QVariant(QObject::tr("TRUB"))
                                 << QVariant(QObject::tr("NATURAL")));
const QList<QVariant> CrudeList(QList<QVariant>() << QVariant(QObject::tr("ROUGH"))
                                 << QVariant(QObject::tr("RHR")));

RefqTreeItem::RefqTreeItem(const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent), m_xcg(0.0), m_zcg(0.0), m_srefCheck(Qt::Unchecked)
    ,m_sref(0.1), m_lrefCheck(Qt::Unchecked), m_lref(0.1), m_latrefCheck(Qt::Unchecked)
    ,m_latref(0.1), m_blayerCheck(Qt::Unchecked), m_blayer(TURB), m_crude(ROUGH)
    ,m_roughCheck(Qt::Unchecked), m_rough(0.0), m_rhrCheck(Qt::Unchecked)
    ,m_rhr(0.0), m_crudeCheck(Qt::Unchecked), m_scaleCheck(Qt::Unchecked), m_scale(1.0)
{

}

void RefqTreeItem::setContent(const CaseContent &caseContent)
{
    QHash<QString, CaseContent> childContent = caseContent.childContent;
    if(childContent.find(REFQKEY) != childContent.end())
    {
        QHash<QString, CaseContent> refqContent = childContent.value(REFQKEY).childContent;
        //XCG
        if(refqContent.find(XCGKEY) != refqContent.end())
        {
            QString xvgValue = refqContent.value(XCGKEY).value.toString();
            m_xcg = xvgValue.toFloat();
        }
        //ZCG
        if(refqContent.find(ZCGKEY) != refqContent.end())
        {
            QString zcgValue = refqContent.value(ZCGKEY).value.toString();
            m_zcg = zcgValue.toFloat();
        }
        //SREF
        if(refqContent.find(SREFKEY) != refqContent.end())
        {
            QString srefValue = refqContent.value(SREFKEY).value.toString();
            m_srefCheck = Qt::Checked;
            m_sref = srefValue.toFloat();
        }
        //LREF
        if(refqContent.find(LREFKEY) != refqContent.end())
        {
            QString lrefValue = refqContent.value(LREFKEY).value.toString();
            m_lref = Qt::Checked;
            m_lref = lrefValue.toFloat();
        }
        //LATREF
        if(refqContent.find(LATREFKEY) != refqContent.end())
        {
            QString latrefValue = refqContent.value(LATREFKEY).value.toString();
            m_latrefCheck = Qt::Checked;
            m_latref = latrefValue.toFloat();
        }
        //BLAYER
        if(refqContent.find(BLAYERKEY) != refqContent.end())
        {
            QString blayerValue = refqContent.value(BLAYERKEY).value.toString();
            if(blayerValue == "TURB")
            {
                m_blayer = TURB;
            }
            else if(blayerValue == "NATURAL")
            {
                m_blayer = NATURAL;
            }
            m_blayerCheck = Qt::Checked;
        }
        //ROUGH
        if(refqContent.find(ROUGHKEY) != refqContent.end())
        {
            QString roughValue = refqContent.value(ROUGHKEY).value.toString();
            m_rough = roughValue.toFloat();
            m_roughCheck = Qt::Checked;
            m_crudeCheck = Qt::Checked;
            m_crude = ROUGH;
        }
        //RHR
        if(refqContent.find(RHRKEY) != refqContent.end())
        {
            QString rhrValue = refqContent.value(RHRKEY).value.toString();
            m_rhr = rhrValue.toFloat();
            m_rhrCheck = Qt::Checked;
            m_crudeCheck = Qt::Checked;
            m_crude = RHR;
        }
        //SCALE
        if(refqContent.find(SCALEKEY) != refqContent.end())
        {
            QString scaleValue = refqContent.value(SCALEKEY).value.toString();
            m_scale = scaleValue.toFloat();
            m_scaleCheck = Qt::Checked;
        }
    }
}

QList<QVariant> RefqTreeItem::getProperty() const
{
    QList<QVariant> propertyItems;

    //LOCATION OF PRESSURE
    PropertyItem locationOfPressureItem = getPropertyItem(LOCATIONOFPRESSUREKEY,
                                                          tr("Location Of Pressure"),
                                                          PROPERTY_TYPE_GROUP);
    QList<QVariant> locationOfPressureChildProperty;

    //XCG
    locationOfPressureChildProperty.append(getPropertyItem(XCGKEY, tr("XCG(L)"),
                                                           PROPERTY_TYPE_DOUBLE, m_xcg,
                                                           0, INFINITYNUMBER, 2));
    //ZCG
    locationOfPressureChildProperty.append(getPropertyItem(ZCGKEY, tr("ZCG(L)"),
                                                           PROPERTY_TYPE_DOUBLE, m_zcg,
                                                           0, INFINITYNUMBER, 2));
    locationOfPressureItem.insert(PropertyConstants::CHILD_PROPERTY, locationOfPressureChildProperty);
    propertyItems.append(locationOfPressureItem);

    //REFERENCE QUANTITY
    PropertyItem referenceQuantityItem = getPropertyItem(REFERENCEQUANTITYKEY,
                                                         tr("Reference Quantity"),
                                                         PROPERTY_TYPE_GROUP);
    QList<QVariant> referenceQuantityChildProperty;
    //SREF
    referenceQuantityChildProperty.append(getPropertyItem(SREFKEY, tr("SREF(L*L)"),
                                                          PROPERTY_TYPE_DOUBLE, m_sref,
                                                          0.01, INFINITYNUMBER, 2, true,
                                                          m_srefCheck));
    //LREF
    referenceQuantityChildProperty.append(getPropertyItem(LREFKEY, tr("LREF(L)"),
                                                          PROPERTY_TYPE_DOUBLE, m_lref,
                                                          0.01, INFINITYNUMBER, 2, true,
                                                          m_lrefCheck));
    //LATREF
    referenceQuantityChildProperty.append(getPropertyItem(LATREFKEY, tr("LATREF(L)"),
                                                          PROPERTY_TYPE_DOUBLE, m_latref,
                                                          0.01, INFINITYNUMBER, 2, true,
                                                          m_latrefCheck));
    referenceQuantityItem.insert(PropertyConstants::CHILD_PROPERTY, referenceQuantityChildProperty);
    propertyItems.append(referenceQuantityItem);

    //BOUNDARY LAYER TYPE
    PropertyItem boundaryLayerTypeItem = getPropertyItem(BOUNDARYLAYERTYPEKEY,
                                                         tr("Boundary Layer Type"),
                                                         PROPERTY_TYPE_GROUP);
    QList<QVariant> boundaryLayerTypeChildProperty;

    //BLAYER
    boundaryLayerTypeChildProperty.append(getPropertyItem(BLAYERKEY, tr("BLAYER"),
                                                          PROPERTY_TYPE_ENUM, m_blayer, 0,
                                                          0, 0, true, m_blayerCheck, BlayerList));
    boundaryLayerTypeItem.insert(PropertyConstants::CHILD_PROPERTY, boundaryLayerTypeChildProperty);
    propertyItems.append(boundaryLayerTypeItem);

    //ROUGHNESS
    PropertyItem roughnessItem = getPropertyItem(ROUGHNESSKEY,
                                                 tr("Roughness"),
                                                 PROPERTY_TYPE_GROUP);
    QList<QVariant> roughnessChildProperty;
    //CRUDE
    roughnessChildProperty.append(getPropertyItem(CRUDEKEY, tr("CRUDE"), PROPERTY_TYPE_ENUM,
                                                  m_crude, 0, 0, 0, true, m_crudeCheck, CrudeList));
    if(m_crude == ROUGH)
    {
        PropertyItem roughItem = getPropertyItem(ROUGHKEY, tr("ROUGH(cm)"),
                                                 PROPERTY_TYPE_DOUBLE, m_rough,
                                                 0, INFINITYNUMBER, 5, true, m_roughCheck);
        roughnessChildProperty.append(roughItem);
    }
    else if(m_crude == RHR)
    {
        PropertyItem rhrItem = getPropertyItem(RHRKEY, tr("RHR"),
                                               PROPERTY_TYPE_DOUBLE, m_rhr,
                                               0, INFINITYNUMBER, 2, true, m_rhrCheck);
        roughnessChildProperty.append(rhrItem);
    }
    roughnessItem.insert(PropertyConstants::CHILD_PROPERTY, roughnessChildProperty);
    propertyItems.append(roughnessItem);

    //SCALE FACTOR
    PropertyItem scaleFactorItem = getPropertyItem(SCALEFACTORKEY,
                                                   tr("Scale Factor"),
                                                   PROPERTY_TYPE_GROUP);
    QList<QVariant> scaleFactorChildProperty;

    //SCALE
    scaleFactorChildProperty.append(getPropertyItem(SCALEKEY, tr("SCALE"),
                                                    PROPERTY_TYPE_DOUBLE, m_scale,
                                                    0.01, INFINITYNUMBER, 2, true, m_scaleCheck));

    scaleFactorItem.insert(PropertyConstants::CHILD_PROPERTY, scaleFactorChildProperty);
    propertyItems.append(scaleFactorItem);

    return propertyItems;
}

void RefqTreeItem::setNewPropertyData(QString objectName, QString value)
{
    if(objectName == XCGKEY)
    {
        m_xcg = value.toFloat();
    }
    else if(objectName == ZCGKEY)
    {
        m_zcg = value.toFloat();
    }
    else if(objectName == SREFKEY)
    {
        m_sref = value.toFloat();
    }
    else if(objectName == LREFKEY)
    {
        m_lref = value.toFloat();
    }
    else if(objectName == LATREFKEY)
    {
        m_latref = value.toFloat();
    }
    else if(objectName == BLAYERKEY)
    {
        m_blayer = (BlayerType)BlayerList.indexOf(value);
    }
    else if(objectName == CRUDEKEY)
    {
        CrudeType crude = (CrudeType)CrudeList.indexOf(value);
        if(crude != m_crude)
        {
            m_crude = crude;
            emit propertiesRebuild();
        }
    }
    else if(objectName == ROUGHKEY)
    {
        m_rough = value.toFloat();
    }
    else if(objectName == RHRKEY)
    {
        m_rhr = value.toFloat();
    }
    else if(objectName == SCALEKEY)
    {
        m_scale = value.toFloat();
    }
}

void RefqTreeItem::setNewPropertyCheckState(QString objectName, Qt::CheckState value)
{
    if(objectName == SREFKEY)
    {
        m_srefCheck = value;
    }
    else if(objectName == LREFKEY)
    {
        m_lrefCheck = value;
    }
    else if(objectName == LATREFKEY)
    {
        m_latrefCheck = value;
    }
    else if(objectName == BLAYERKEY)
    {
        m_blayerCheck = value;
    }
    else if(objectName == CRUDEKEY)
    {
        m_crudeCheck = value;
    }
    else if(objectName == ROUGHKEY)
    {
        m_roughCheck = value;
    }
    else if(objectName == RHRKEY)
    {
        m_rhrCheck = value;
    }
    else if(objectName == SCALEKEY)
    {
        m_scaleCheck = value;
    }
}

float RefqTreeItem::getXCGValue() const
{
    return m_xcg;
}
