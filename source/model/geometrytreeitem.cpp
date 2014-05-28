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

GeometryTreeItem::GeometryTreeItem(const QList<QVariant> &data, TreeItem *parent)
    :TreeItem(data, parent)
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
            QHash<QString, CaseContent> axibodContent = childContent.value(AXIBODKEY).childContent;
            //LNOSE
            if(axibodContent.find(LNOSEKEY) != axibodContent.end())
            {
                QString lnoseValue = axibodContent.value(LNOSEKEY).value.toString();
                m_lonse = lnoseValue.toFloat();
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
                    m_trunc = true;
                }
                else if(truncValue == "FALSE")
                {
                    m_trunc = false;
                }
            }
            //BNOSE
            if(axibodContent.find(BNOSEKEY) != axibodContent.end())
            {
                QString bnoseValue = axibodContent.value(BNOSEKEY).value.toString();
                m_bnose = bnoseValue.toFloat();
                m_truncCheck = Qt::Checked;
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
                m_decntr = dcentrValue.toFloat();
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
        }
        else if(childContent.find(ELLBODKEY) != childContent.end())
        {

        }
    }
}

QList<QVariant> GeometryTreeItem::getProperty() const
{
    return QList<QVariant>();
}

void GeometryTreeItem::setNewPropertyData(QString objectName, QString value)
{
}

void GeometryTreeItem::setNewPropertyCheckState(QString objectName, Qt::CheckState value)
{
}
