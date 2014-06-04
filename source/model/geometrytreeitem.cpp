#include "geometrytreeitem.h"

const QLatin1String AXIBODKEY("AXIBOD");
const QLatin1String ELLBODKEY("ELLBOD");
const QLatin1String LNOSEKEY("LNOSE");
const QLatin1String DNOSEKEY("DNOSE");
const QLatin1String TNOSEKEY("TNOSE");
const QLatin1String POWERKEY("POWER");
const QLatin1String TRUNCKEY("TRUNC");
const QLatin1String BNOSEKEY("BNOSE");
const QLatin1String LCENTRKEY("LCENTR");
const QLatin1String DCENTRKEY("DCENTR");
const QLatin1String LAFTKEY("LAFT");
const QLatin1String DAFTKEY("DAFT");
const QLatin1String TAFTKEY("TAFT");
const QLatin1String DEXITKEY("DEXIT");
const QLatin1String BASEKEY("BASE");
const QLatin1String BETANKEY("BETANKEY");
const QLatin1String JMACHKEY("JMACH");
const QLatin1String PRATKEY("PART");
const QLatin1String TRATKEY("TRAT");
const QLatin1String XOKEY("XO");
const QLatin1String NXKEY("NX");
const QLatin1String XKEY("X");
const QLatin1String RKEY("R");
const QLatin1String DISCONKEY("DISCON");
const QLatin1String WNOSEKEY("WNOSE");
const QLatin1String ENOSEKEY("ENOSE");
const QLatin1String WCENTRKEY("WCENTR");
const QLatin1String ECENTRKEY("ECENTR");
const QLatin1String WAFTKEY("WAFT");
const QLatin1String EAFTKEY("EAFT");
const QLatin1String WKEY("W");
const QLatin1String HKEY("H");
const QLatin1String ELLIPKEY("ELLIP");
const QLatin1String HEADTYPEKEY("HEADTYPE");

const QList<QVariant> TnoseList(QList<QVariant>() << QVariant(QObject::tr("CONICAL"))
                                << QVariant(QObject::tr("OGVIE")) << QVariant(QObject::tr("POWER"))
                                << QVariant(QObject::tr("HAACK")) << QVariant(QObject::tr("KARMAN")));

const QList<QVariant> HeadTypeList(QList<QVariant>() << QVariant(QObject::tr("PASSIVATE"))
                                   << QVariant(QObject::tr("TRUNCATE")));

const QList<QVariant> TaftList(QList<QVariant>() << QVariant(QObject::tr("CONICAL(CONE)"))
                               << QVariant(QObject::tr("OGVIE")));

GeometryTreeItem::GeometryTreeItem(const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent), m_lnose(0.0), m_dnose(0.0), m_tnose(TNOSE_OGVIE),
      m_power(0.0), m_headType(PASSIVATE), m_bnose(0.0),
      m_lcentr(0.0), m_dcentr(0.0), m_laft(0.0), m_daft(0.01), m_taft(TAFT_CONICAL),
      m_dexit(0.0), m_base(false), m_betan(0.0), m_xoCheck(Qt::Unchecked), m_xo(0.0),
      m_nx(0), m_x(0.0), m_r(0.0), m_wnose(1.0), m_enose(1.0), m_wcentr(1.0), m_ecentr(1.0),
      m_waft(0.01), m_eaft(1.0), m_ellipseType(W_H), m_type(AXIBOD)
{
}

void GeometryTreeItem::setContent(const CaseContent &caseContent)
{
    QHash<QString, CaseContent>::const_iterator iter;
    for(iter = caseContent.childContent.begin();iter != caseContent.childContent.end(); iter++)
    {
        QHash<QString, CaseContent> childContent = caseContent.childContent;
        if(childContent.find(AXIBODKEY) != childContent.end())
        {
            m_type = AXIBOD;
            QHash<QString, CaseContent> axibodContent = childContent.value(AXIBODKEY).childContent;
            //LNOSE
            if(axibodContent.find(LNOSEKEY) != axibodContent.end())
            {
                QString lnoseValue = axibodContent.value(LNOSEKEY).value.toString();
                m_lnose = lnoseValue.toFloat();
            }
            //DNOSE
            if(axibodContent.find(DNOSEKEY) != axibodContent.end())
            {
                QString dnoseValue = axibodContent.value(DNOSEKEY).value.toString();
                m_dnose = dnoseValue.toFloat();
            }
            //TNOSE
            if(axibodContent.find(TNOSEKEY) != axibodContent.end())
            {
                QString tnoseValue = axibodContent.value(TNOSEKEY).value.toString();
                if(tnoseValue == "CONICAL")
                {
                    m_tnose = TNOSE_CONICAL;
                }
                else if(tnoseValue == "OGVIE")
                {
                    m_tnose = TNOSE_OGVIE;
                }
                else if(tnoseValue == "POWER")
                {
                    m_tnose = TNOSE_POWER;
                }
                else if(tnoseValue == "HAACK")
                {
                    m_tnose = TNOSE_HAACK;
                }
                else if(tnoseValue == "KARMAN")
                {
                    m_tnose = TNOSE_KARMAN;
                }
            }
            //POWER
            if(axibodContent.find(POWERKEY) != axibodContent.end())
            {
                QString powerValue = axibodContent.value(POWERKEY).value.toString();
                m_power = powerValue.toFloat();
            }
            //TRUNC
            if(axibodContent.find(TRUNCKEY) != axibodContent.end())
            {
                QString truncValue = axibodContent.value(TRUNCKEY).value.toString();
                if(truncValue == "TRUE")
                {
                    m_headType = TRUNCATE;
                }
                else if(truncValue == "FALSE")
                {
                    m_headType = PASSIVATE;
                }
            }
            //BNOSE
            if(axibodContent.find(BNOSEKEY) != axibodContent.end())
            {
                QString bnoseValue = axibodContent.value(BNOSEKEY).value.toString();
                m_bnose = bnoseValue.toFloat();
            }
            //LCENTR
            if(axibodContent.find(LCENTRKEY) != axibodContent.end())
            {
                QString lcentrValue = axibodContent.value(LCENTRKEY).value.toString();
                m_lcentr = lcentrValue.toFloat();
            }
            //DCENTR
            if(axibodContent.find(DCENTRKEY) != axibodContent.end())
            {
                QString dcentrValue = axibodContent.value(DCENTRKEY).value.toString();
                m_dcentr = dcentrValue.toFloat();
            }
            //LAFT
            if(axibodContent.find(LAFTKEY) != axibodContent.end())
            {
                QString laftValue = axibodContent.value(LAFTKEY).value.toString();
                m_laft = laftValue.toFloat();
            }
            //DAFT
            if(axibodContent.find(DAFTKEY) != axibodContent.end())
            {
                QString daftValue = axibodContent.value(DAFTKEY).value.toString();
                m_daft = daftValue.toFloat();
            }
            //TAFT
            if(axibodContent.find(TAFTKEY) != axibodContent.end())
            {
                QString taftValue = axibodContent.value(TAFTKEY).value.toString();
                if(taftValue == "CONICAL")
                {
                    m_taft = TAFT_CONICAL;
                }
                else if(taftValue == "OGVIE")
                {
                    m_taft = TAFT_OGVIE;
                }
                m_taftCheck = Qt::Checked;
            }
            //DEXIT
            if(axibodContent.find(DEXITKEY) != axibodContent.end())
            {
                QString dexitValue = axibodContent.value(DEXITKEY).value.toString();
                m_dexit = dexitValue.toFloat();
            }
            //BASE
            if(axibodContent.find(BASEKEY) != axibodContent.end())
            {
                QString baseValue = axibodContent.value(BASEKEY).value.toString();
                if(baseValue == "TRUE")
                {
                    m_base = true;
                }
                else if(baseValue == "FALSE")
                {
                    m_base = false;
                }
            }
            //BETAN
            if(axibodContent.find(BETANKEY) != axibodContent.end())
            {
                QString betanValue = axibodContent.value(BETANKEY).value.toString();
                m_betan = betanValue.toFloat();
            }
            //JMACH
            if(axibodContent.find(JMACHKEY) != axibodContent.end())
            {
                QString jmachValue = axibodContent.value(JMACHKEY).value.toString();
                QStringList jmachList = jmachValue.split(",");
                QString jmachStr;
                for(int i = 0, iend = jmachList.size(); i < iend; i++)
                {
                    jmachStr = jmachStr + QString::number(jmachList[i].toFloat(), 'f', 2) + ",";
                }
                m_jmach = jmachStr;
            }
            //PRAT
            if(axibodContent.find(PRATKEY) != axibodContent.end())
            {
                QString pratValue = axibodContent.value(PRATKEY).value.toString();
                QStringList pratList = pratValue.split(",");
                QString pratStr;
                for(int i = 0, iend = pratList.size(); i < iend; i++)
                {
                    pratStr = pratStr + QString::number(pratList[i].toFloat(), 'f', 2) + ",";
                }
                m_prat = pratStr;
            }
            //TRAT
            if(axibodContent.find(TRATKEY) != axibodContent.end())
            {
                QString tratValue = axibodContent.value(TRATKEY).value.toString();
                QStringList tratList = tratValue.split(",");
                QString tratStr;
                for(int i = 0, iend = tratList.size(); i < iend; i++)
                {
                    tratStr = tratStr + QString::number(tratList[i].toFloat(), 'f', 2) + ",";
                }
                m_trat = tratStr;
            }
            //XO
            if(axibodContent.find(XOKEY) != axibodContent.end())
            {
                QString xoValue = axibodContent.value(XOKEY).value.toString();
                m_xo = xoValue.toFloat();
                m_xoCheck = Qt::Checked;
            }

            /////////////////////////////////////////////////////////////////////////
            //NX
            if(axibodContent.find(NXKEY) != axibodContent.end())
            {
                QString nxValue = axibodContent.value(NXKEY).value.toString();
                m_nx = nxValue.toInt();
                m_type = AXIBOD_NX;
            }
            //X
            if(axibodContent.find(XKEY) != axibodContent.end())
            {
                QString xValue = axibodContent.value(XKEY).value.toString();
                m_x = xValue.toFloat();
            }
            //R
            if(axibodContent.find(RKEY) != axibodContent.end())
            {
                QString rValue = axibodContent.value(RKEY).value.toString();
                m_r = rValue.toFloat();
            }
            //DISCON
            if(axibodContent.find(DISCONKEY) != axibodContent.end())
            {
                QString disconValue = axibodContent.value(DISCONKEY).value.toString();
                QStringList disconList = disconValue.split(",");
                QString disconStr;
                for(int i = 0, iend = disconList.size(); i < iend; i++)
                {
                    disconStr = disconStr + QString::number(disconList[i].toFloat(), 'f', 2) + ",";
                }
                m_discon = disconStr;
            }
        }
        else if(childContent.find(ELLBODKEY) != childContent.end())
        {
            m_type = ELLBOD;
            QHash<QString, CaseContent> ellbodContent = childContent.value(ELLBODKEY).childContent;
            //LNOSE
            if(ellbodContent.find(LNOSEKEY) != ellbodContent.end())
            {
                QString lnoseValue = ellbodContent.value(LNOSEKEY).value.toString();
                m_lnose = lnoseValue.toFloat();
            }
            //WNOSE
            if(ellbodContent.find(WNOSEKEY) != ellbodContent.end())
            {
                QString wnoseValue = ellbodContent.value(WNOSEKEY).value.toString();
                m_wnose = wnoseValue.toFloat();
            }
            //ENOSE
            if(ellbodContent.find(ENOSEKEY) != ellbodContent.end())
            {
                QString enoseValue = ellbodContent.value(ENOSEKEY).value.toString();
                m_enose = enoseValue.toFloat();
            }
            //TNOSE
            if(ellbodContent.find(TNOSEKEY) != ellbodContent.end())
            {
                QString tnoseValue = ellbodContent.value(TNOSEKEY).value.toString();
                if(tnoseValue == "CONICAL")
                {
                    m_tnose = TNOSE_CONICAL;
                }
                else if(tnoseValue == "OGVIE")
                {
                    m_tnose = TNOSE_OGVIE;
                }
                else if(tnoseValue == "POWER")
                {
                    m_tnose = TNOSE_POWER;
                }
                else if(tnoseValue == "HAACK")
                {
                    m_tnose = TNOSE_HAACK;
                }
                else if(tnoseValue == "KARMAN")
                {
                    m_tnose = TNOSE_KARMAN;
                }
            }
            //POWER
            if(ellbodContent.find(POWERKEY) != ellbodContent.end())
            {
                QString powerValue = ellbodContent.value(POWERKEY).value.toString();
                m_power = powerValue.toFloat();
            }
            //TRUNC
            if(ellbodContent.find(TRUNCKEY) != ellbodContent.end())
            {
                QString truncValue = ellbodContent.value(TRUNCKEY).value.toString();
                if(truncValue == "TRUE")
                {
                    m_headType = TRUNCATE;
                }
                else if(truncValue == "FALSE")
                {
                    m_headType = PASSIVATE;
                }
            }
            //BNOSE
            if(ellbodContent.find(BNOSEKEY) != ellbodContent.end())
            {
                QString bnoseValue = ellbodContent.value(BNOSEKEY).value.toString();
                m_bnose = bnoseValue.toFloat();
            }
            //LCENTR
            if(ellbodContent.find(LCENTRKEY) != ellbodContent.end())
            {
                QString lcentrValue = ellbodContent.value(LCENTRKEY).value.toString();
                m_lcentr = lcentrValue.toFloat();
            }
            //WCENTR
            if(ellbodContent.find(WCENTRKEY) != ellbodContent.end())
            {
                QString wcentrValue = ellbodContent.value(WCENTRKEY).value.toString();
                m_wcentr = wcentrValue.toFloat();
            }
            //ECENTR
            if(ellbodContent.find(ECENTRKEY) != ellbodContent.end())
            {
                QString ecentrValue = ellbodContent.value(ECENTRKEY).value.toString();
                m_ecentr = ecentrValue.toFloat();
            }
            //LAFT
            if(ellbodContent.find(LAFTKEY) != ellbodContent.end())
            {
                QString laftValue = ellbodContent.value(LAFTKEY).value.toString();
                m_laft = laftValue.toFloat();
            }
            //WAFT
            if(ellbodContent.find(WAFTKEY) != ellbodContent.end())
            {
                QString waftValue = ellbodContent.value(WAFTKEY).value.toString();
                m_waft = waftValue.toFloat();
            }
            //EAFT
            if(ellbodContent.find(EAFTKEY) != ellbodContent.end())
            {
                QString eaftValue = ellbodContent.value(EAFTKEY).value.toString();
                m_eaft = eaftValue.toFloat();
            }
            //TAFT
            if(ellbodContent.find(TAFTKEY) != ellbodContent.end())
            {
                QString taftValue = ellbodContent.value(TAFTKEY).value.toString();
                if(taftValue == "CONICAL")
                {
                    m_taft = TAFT_CONICAL;
                }
                else if(taftValue == "OGVIE")
                {
                    m_taft = TAFT_OGVIE;
                }
                m_taftCheck = Qt::Checked;
            }
            //DEXIT
            if(ellbodContent.find(DEXITKEY) != ellbodContent.end())
            {
                QString dexitValue = ellbodContent.value(DEXITKEY).value.toString();
                m_dexit = dexitValue.toFloat();
            }
            //XO
            if(ellbodContent.find(XOKEY) != ellbodContent.end())
            {
                QString xoValue = ellbodContent.value(XOKEY).value.toString();
                m_xo = xoValue.toFloat();
                m_xoCheck = Qt::Checked;
            }
            /////////////////////////////////////////////////////////////////////////
            //NX
            if(ellbodContent.find(NXKEY) != ellbodContent.end())
            {
                m_type = ELLBOD_NX;
                QString nxValue = ellbodContent.value(NXKEY).value.toString();
                m_nx = nxValue.toInt();
            }
            //X
            if(ellbodContent.find(XKEY) != ellbodContent.end())
            {
                QString xValue = ellbodContent.value(XKEY).value.toString();
                m_x = xValue.toFloat();
            }
            //ELLIPSE --- W AND H
            if(ellbodContent.find(WKEY) != ellbodContent.end() && ellbodContent.find(HKEY) != ellbodContent.end())
            {
                QString wValue = ellbodContent.value(WKEY).value.toString();
                QStringList wList = wValue.split(",");
                QString wStr;
                for(int i = 0, iend = wList.size(); i < iend; i++)
                {
                    wStr = wStr + QString::number(wList[i].toFloat(), 'f', 2) + ",";
                }
                m_w = wStr;

                QString hValue = ellbodContent.value(HKEY).value.toString();
                QStringList hList = hValue.split(",");
                QString hStr;
                for(int i = 0, iend = hList.size(); i < iend; i++)
                {
                    hStr = hStr + QString::number(hList[i].toFloat(), 'f', 2) + ",";
                }
                m_h = hStr;

                m_ellipseType = W_H;
            }
            //ELLIPSE --- W AND ELLIP
            if(ellbodContent.find(WKEY) != ellbodContent.end() && ellbodContent.find(ELLIPKEY) != ellbodContent.end())
            {
                QString wValue = ellbodContent.value(WKEY).value.toString();
                QStringList wList = wValue.split(",");
                QString wStr;
                for(int i = 0, iend = wList.size(); i < iend; i++)
                {
                    wStr = wStr + QString::number(wList[i].toFloat(), 'f', 2) + ",";
                }
                m_w = wStr;

                QString ellipValue = ellbodContent.value(ELLBODKEY).value.toString();
                QStringList ellipList = ellipValue.split(",");
                QString ellipStr;
                for(int i = 0, iend = ellipList.size(); i < iend; i++)
                {
                    ellipStr= ellipStr + QString::number(ellipList[i].toFloat(), 'f', 2) + ",";
                }
                m_ellip = ellipStr;

                m_ellipseType = W_ELLIP;
            }
            //ELLIPSE --- H AND ELLIP
            if(ellbodContent.find(HKEY) != ellbodContent.end() && ellbodContent.find(ELLIPKEY) != ellbodContent.end())
            {
                QString hValue = ellbodContent.value(HKEY).value.toString();
                QStringList hList = hValue.split(",");
                QString hStr;
                for(int i = 0, iend = hList.size(); i < iend; i++)
                {
                    hStr = hStr + QString::number(hList[i].toFloat(), 'f', 2) + ",";
                }
                m_h = hStr;

                QString ellipValue = ellbodContent.value(ELLBODKEY).value.toString();
                QStringList ellipList = ellipValue.split(",");
                QString ellipStr;
                for(int i = 0, iend = ellipList.size(); i < iend; i++)
                {
                    ellipStr= ellipStr + QString::number(ellipList[i].toFloat(), 'f', 2) + ",";
                }
                m_ellip = ellipStr;

                m_ellipseType = H_ELLIP;
            }
            //DISCON
            if(ellbodContent.find(DISCONKEY) != ellbodContent.end())
            {
                QString disconValue = ellbodContent.value(DISCONKEY).value.toString();
                QStringList disconList = disconValue.split(",");
                QString disconStr;
                for(int i = 0, iend = disconList.size(); i < iend; i++)
                {
                    disconStr = disconStr + QString::number(disconList[i].toFloat(), 'f', 2) + ",";
                }
                m_discon = disconStr;
            }
        }
    }
}

QList<QVariant> GeometryTreeItem::getProperty() const
{
    QList<QVariant> propertyItems;
    switch(m_type)
    {
    case AXIBOD:
    {
        //LNOSE
        propertyItems.append(getPropertyItem(LNOSEKEY, tr("LNOSE(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_lnose,
                                             0.0, INFINITYNUMBER, 2));
        //DNOSE
        propertyItems.append(getPropertyItem(DNOSEKEY, tr("DNOSE(L*L)"),
                                             PROPERTY_TYPE_DOUBLE, m_dnose,
                                             0.0, INFINITYNUMBER, 2));
        //TNOSE
        if(m_tnose == TNOSE_POWER)
        {
            PropertyItem tnoseGroupItem = getPropertyItem(TNOSEKEY, tr("TNOSE"),
                                                          PROPERTY_TYPE_ENUM_GROUP, m_tnose,
                                                          0, 0, 0, false, Qt::Unchecked, TnoseList);
            QList<QVariant> tnoseChildProperty;
            //POWER
            PropertyItem powerItem = getPropertyItem(POWERKEY, tr("POWER"),
                                                     PROPERTY_TYPE_DOUBLE, m_power, 0.0,
                                                     1.0, 2);
            tnoseChildProperty.append(powerItem);

            tnoseGroupItem.insert(PropertyConstants::CHILD_PROPERTY, tnoseChildProperty);
            propertyItems.append(tnoseGroupItem);
        }
        else
        {
            propertyItems.append(getPropertyItem(TNOSEKEY, tr("TNOSE"),
                                                 PROPERTY_TYPE_ENUM, m_tnose,
                                                 0, 0, 0, false, Qt::Unchecked, TnoseList));
        }
        //HEADTYPE
        propertyItems.append(getPropertyItem(HEADTYPEKEY, tr("HEADTYPE"),
                                             PROPERTY_TYPE_ENUM, m_headType,
                                             0, 0, 0, false, Qt::Unchecked, HeadTypeList));
        //BNOSE
        propertyItems.append(getPropertyItem(BNOSEKEY, tr("BNOSE(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_bnose,
                                             0.0, INFINITYNUMBER, 2));
        //LCENTR
        propertyItems.append(getPropertyItem(LCENTRKEY, tr("LCENTR(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_lcentr,
                                             0.0, INFINITYNUMBER, 2));
        //DCENTR
        propertyItems.append(getPropertyItem(DCENTRKEY, tr("DCENTR(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_dcentr,
                                             0.01, INFINITYNUMBER, 2));
        //LAFT
        propertyItems.append(getPropertyItem(LAFTKEY, tr("LAFT(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_laft,
                                             0.0, INFINITYNUMBER, 2));
        //DAFT
        propertyItems.append(getPropertyItem(DAFTKEY, tr("DAFT(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_daft,
                                             0.01, INFINITYNUMBER, 2));
        //TAFT
        propertyItems.append(getPropertyItem(TAFTKEY, tr("TAFT"),
                                             PROPERTY_TYPE_ENUM, m_taft,
                                             0, 0, 0, true, m_taftCheck, TaftList));
        //DEXIT
        propertyItems.append(getPropertyItem(DEXITKEY, tr("DEXIT(L)"),
                                             PROPERTY_TYPE_DOUBLE, m_dexit,
                                             0, m_daft, 2));
        //BASE
        propertyItems.append(getPropertyItem(BASEKEY, tr("BASE"),
                                             PROPERTY_TYPE_BOOL, m_base));

        //BETAN-JMACH-PRAT-TRAT
        if(m_base && m_dexit - 0.0 < 0.0001)
        {
            FltconTreeItem *fltConTreeItem = NULL;
            for(int i = 0, iend = m_parentItem->childCount(); i < iend; i++)
            {
                fltConTreeItem = qobject_cast<FltconTreeItem *>(m_parentItem->child(i));
                if(fltConTreeItem)
                {
                    break;
                }
            }
            int count = fltConTreeItem->getNamchOrNvinf();
            //BETAN
            propertyItems.append(getPropertyItem(BETANKEY, tr("BETAN(deg)"),
                                                 PROPERTY_TYPE_DOUBLE, m_betan,
                                                 0.0, 90.0, 2));
            //JMACH
            QString jmachPattern;
            for(int i = 0, iend = count; i < iend; i++)
            {
                jmachPattern.append("[0-9]\\d{0,1}.[0-9]\\d{0,1},");
            }
            propertyItems.append(getPropertyItem(JMACHKEY, tr("JMACH"),
                                                 PROPERTY_TYPE_STRING_REG, m_jmach,
                                                 0, 0, 0, false, Qt::Unchecked, QList<QVariant>(),
                                                 true, jmachPattern));
            //PRAT
            QString pratPattern;
            for(int i = 0, iend = count; i < iend; i++)
            {
                pratPattern.append("[0-9]\\d{0,1}.[0-9]\\d{0,1},");
            }
            propertyItems.append(getPropertyItem(PRATKEY, tr("PRAT"),
                                                 PROPERTY_TYPE_STRING_REG, m_prat,
                                                 0, 0, 0, false, Qt::Unchecked, QList<QVariant>(),
                                                 true, pratPattern));
            //TRAT
            QString tratPattern;
            for(int i = 0, iend = count; i < iend; i++)
            {
                tratPattern.append("[0-9]\\d{0,1}.[0-9]\\d{0,1},");
            }
            propertyItems.append(getPropertyItem(TRATKEY, tr("TRAT"),
                                                 PROPERTY_TYPE_STRING_REG, m_trat,
                                                 0, 0, 0, false, Qt::Unchecked, QList<QVariant>(),
                                                 true, tratPattern));
        }
        //XO
        RefqTreeItem *refqTreeItem = NULL;
        for(int i = 0, iend = m_parentItem->childCount(); i < iend; i++)
        {
            refqTreeItem = qobject_cast<RefqTreeItem *>(m_parentItem->child(i));
            if(refqTreeItem)
            {
                break;
            }
        }
        float xcg = refqTreeItem->getXCGValue();
        propertyItems.append(getPropertyItem(XOKEY, tr("XO"),
                                             PROPERTY_TYPE_DOUBLE, m_xo,
                                             0.0, xcg, 2));
        break;
    }
    default:
    {
        break;
    }
    }

    return propertyItems;
}

void GeometryTreeItem::setNewPropertyData(QString objectName, QString value)
{
}

void GeometryTreeItem::setNewPropertyCheckState(QString objectName, Qt::CheckState value)
{
}
