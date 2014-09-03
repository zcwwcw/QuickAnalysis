#include "finsetchildtreeitem.h"

const QLatin1String SECTYPEKEY("SECTYPE");
const QLatin1String SSPANKEY("SSPAN");
const QLatin1String CHORDKEY("CHORD");
const QLatin1String XLEKEY("XLE");
const QLatin1String XLE1KEY("XLE(1)");
const QLatin1String SWEEPKEY("SWEEP");
const QLatin1String STAKEY("STA");
const QLatin1String LERKEY("LER");
const QLatin1String NPANELKEY("NPANEL");
const QLatin1String PHIFKEY("PHIF");
const QLatin1String GAMKEY("GAM");
const QLatin1String CFOCKEY("CFOC");
const QLatin1String ZUPPERKEY("ZUPPER");
const QLatin1String ZLOWERKEY("ZLOWER");
const QLatin1String LMAXUKEY("LMAXU");
const QLatin1String LMAXLKEY("LMAXL");
const QLatin1String LFLATUKEY("LFLATU");
const QLatin1String LFLATLKEY("LFLATL");
const QLatin1String XCORDKEY("XCORD");
const QLatin1String MEANKEY("MEAN");
const QLatin1String THICKKEY("THICK");
const QLatin1String YUPPERKEY("YUPPER");
const QLatin1String YLOWERKEY("YLOWER");

const QList<QVariant> sectypeList(QList<QVariant>() << QVariant(QObject::tr("HEX")) << QVariant(QObject::tr("ARC"))
                                   << QVariant(QObject::tr("USER")) << QVariant(QObject::tr("NACA")));

FinsetChildTreeItem::FinsetChildTreeItem(const QList<QVariant> &data, TreeItem *parent) :
    TreeItem(data, parent), m_secType(HEX), m_xleType(XLE)
{
}

void FinsetChildTreeItem::setContent(const CaseContent &caseContent)
{
    if(m_key.isEmpty())
    {
        return;
    }
    QHash<QString, CaseContent> childContent = caseContent.childContent;
    if(childContent.find(m_key) != childContent.end())
    {
        QHash<QString, CaseContent> finsetContent = childContent.value(m_key).childContent;
        //SECTYPE
        if(finsetContent.find(SECTYPEKEY) != finsetContent.end())
        {
            QString sectypeValue = finsetContent.value(SECTYPEKEY).value.toString();
            if(sectypeValue == "HEX")
            {
                m_secType = HEX;
            }
            else if(sectypeValue == "ARC")
            {
                m_secType = ARC;
            }
            else if(sectypeValue == "USER")
            {
                m_secType = USER;
            }
            else if(sectypeValue == "NACA")
            {
                m_secType = NACA;
            }
        }
        //SSPAN
        if(finsetContent.find(SSPANKEY) != finsetContent.end())
        {
            QString sspanValue = finsetContent.value(SSPANKEY).value.toString();
            QStringList sspanList = sspanValue.split(",");
            QString sspanStr;
            for(int i = 0, iend = sspanList.size(); i < iend; i++)
            {
                sspanStr = sspanStr + QString::number(sspanList[i].toFloat(), 'f', 1) + ",";
            }
            m_sspan = sspanStr;
        }
        //CHORD
        if(finsetContent.find(CHORDKEY) != finsetContent.end())
        {
            QString chordValue = finsetContent.value(CHORDKEY).value.toString();
            QStringList chordList = chordValue.split(",");
            QString chordStr;
            for(int i = 0, iend = chordList.size(); i < iend; i++)
            {
                chordStr = chordStr + QString::number(chordList[i].toFloat(), 'f', 1) + ",";
            }
            m_chord = chordStr;
        }
        //XLE
        if(finsetContent.find(XLEKEY) != finsetContent.end())
        {
            QString xleValue = finsetContent.value(XLEKEY).value.toString();
            QStringList xleList = xleValue.split(",");
            QString xleStr;
            for(int i = 0, iend = xleList.size(); i < iend; i++)
            {
                xleStr = xleStr + QString::number(xleList[i].toFloat(), 'f', 1) + ",";
            }
            m_xle = xleStr;
        }
        //XLE1
        if(finsetContent.find(XLE1KEY) != finsetContent.end())
        {
            m_xle1 = finsetContent.value(XLE1KEY).value.toFloat();
        }
        //SWEEP
        if(finsetContent.find(SWEEPKEY) != finsetContent.end())
        {
            QString sweepValue = finsetContent.value(SWEEPKEY).value.toString();
            QStringList sweepList = sweepValue.split(",");
            QString sweepStr;
            for(int i = 0, iend = sweepList.size(); i < iend; i++)
            {
                sweepStr = sweepStr + QString::number(sweepList[i].toFloat(), 'f', 1) + ",";
            }
            m_sweep = sweepStr;
        }
        //STA
        if(finsetContent.find(STAKEY) != finsetContent.end())
        {
            QString staValue = finsetContent.value(STAKEY).value.toString();
            QStringList staList = staValue.split(",");
            QString staStr;
            for(int i = 0, iend = staList.size(); i < iend; i++)
            {
                staStr = staStr + QString::number(staList[i].toFloat(), 'f', 1) + ",";
            }
            m_sta = staStr;
        }
        //LER
        if(finsetContent.find(LERKEY) != finsetContent.end())
        {
            QString lerValue = finsetContent.value(LERKEY).value.toString();
            QStringList lerList = lerValue.split(",");
            QString lerStr;
            for(int i = 0, iend = lerList.size(); i < iend; i++)
            {
                lerStr = lerStr + QString::number(lerList[i].toFloat(), 'f', 1) + ",";
            }
            m_ler = lerStr;
        }
        //NPANEL
        if(finsetContent.find(NPANELKEY) != finsetContent.end())
        {
            m_npael = finsetContent.value(NPANELKEY).value.toInt();
        }
        //PHIF
        if(finsetContent.find(PHIFKEY) != finsetContent.end())
        {
            QString phifValue = finsetContent.value(PHIFKEY).value.toString();
            QStringList phifList = phifValue.split(",");
            QString phifStr;
            for(int i = 0, iend = phifList.size(); i < iend; i++)
            {
                phifStr = phifStr + QString::number(phifList[i].toFloat(), 'f', 2) + ",";
            }
            m_phif = phifStr;
        }
        //GAM
        if(finsetContent.find(GAMKEY) != finsetContent.end())
        {
            QString gamValue = finsetContent.value(GAMKEY).value.toString();
            QStringList gamList = gamValue.split(",");
            QString gamStr;
            for(int i = 0, iend = gamList.size(); i < iend; i++)
            {
                gamStr = gamStr + QString::number(gamList[i].toFloat(), 'f', 2) + ",";
            }
            m_gam = gamStr;
        }
        //CFOC
        if(finsetContent.find(CFOCKEY) != finsetContent.end())
        {
            QString cfocValue = finsetContent.value(GAMKEY).value.toString();
            QStringList cfocList = cfocValue.split(",");
            QString cfocStr;
            for(int i = 0, iend = cfocList.size(); i < iend; i++)
            {
                cfocStr = cfocStr + QString::number(cfocList[i].toFloat(), 'f', 3) + ",";
            }
            m_cfoc = cfocStr;
        }
        //ZUPPER
        if(finsetContent.find(ZUPPERKEY) != finsetContent.end())
        {
            QString zupperValue = finsetContent.value(GAMKEY).value.toString();
            QStringList zupperList = zupperValue.split(",");
            QString zupperStr;
            for(int i = 0, iend = zupperList.size(); i < iend; i++)
            {
                zupperStr = zupperStr + QString::number(zupperList[i].toFloat(), 'f', 3) + ",";
            }
            m_zupper = zupperStr;
        }
        //ZLOWER
        if(finsetContent.find(ZLOWERKEY) != finsetContent.end())
        {
            QString zlowerValue = finsetContent.value(ZLOWERKEY).value.toString();
            QStringList zlowerList = zlowerValue.split(",");
            QString zlowerStr;
            for(int i = 0, iend = zlowerList.size(); i < iend; i++)
            {
                zlowerStr = zlowerStr + QString::number(zlowerList[i].toFloat(), 'f', 3) + ",";
            }
            m_zlower = zlowerStr;
        }
        //LMAXU
        if(finsetContent.find(LMAXUKEY) != finsetContent.end())
        {
            QString lmaxuValue = finsetContent.value(LMAXUKEY).value.toString();
            QStringList lmaxuList = lmaxuValue.split(",");
            QString lmaxuStr;
            for(int i = 0, iend = lmaxuList.size(); i < iend; i++)
            {
                lmaxuStr = lmaxuStr + QString::number(lmaxuList[i].toFloat(), 'f', 3) + ",";
            }
            m_lmaxu = lmaxuStr;
        }
        //LMAXL
        if(finsetContent.find(LMAXLKEY) != finsetContent.end())
        {
            QString lmaxlValue = finsetContent.value(LMAXLKEY).value.toString();
            QStringList lmaxlList = lmaxlValue.split(",");
            QString lmaxlStr;
            for(int i = 0, iend = lmaxlList.size(); i < iend; i++)
            {
                lmaxlStr = lmaxlStr + QString::number(lmaxlList[i].toFloat(), 'f', 3) + ",";
            }
            m_lmaxl = lmaxlStr;
        }
        //LFLATU
        if(finsetContent.find(LFLATUKEY) != finsetContent.end())
        {
            QString lflatuValue = finsetContent.value(LFLATUKEY).value.toString();
            QStringList lflatuList = lflatuValue.split(",");
            QString lflatuStr;
            for(int i = 0, iend = lflatuList.size(); i < iend; i++)
            {
                lflatuStr = lflatuStr + QString::number(lflatuList[i].toFloat(), 'f', 3) + ",";
            }
            m_lflatu = lflatuStr;
        }
        //LFLATL
        if(finsetContent.find(LFLATLKEY) != finsetContent.end())
        {
            QString lflatlValue = finsetContent.value(LFLATLKEY).value.toString();
            QStringList lflatlList = lflatlValue.split(",");
            QString lflatlStr;
            for(int i = 0, iend = lflatlList.size(); i < iend; i++)
            {
                lflatlStr = lflatlStr + QString::number(lflatlList[i].toFloat(), 'f', 3) + ",";
            }
            m_lflatl = lflatlStr;
        }
        //XCORD
        if(finsetContent.find(XCORDKEY) != finsetContent.end())
        {
            QString xcordValue = finsetContent.value(XCORDKEY).value.toString();
            QStringList xcordList = xcordValue.split(",");
            QString xcordStr;
            for(int i = 0, iend = xcordList.size(); i < iend; i++)
            {
                xcordStr = xcordStr + QString::number(xcordList[i].toFloat(), 'f', 3) + ",";
            }
            m_xcord = xcordStr;
        }
        //MEAN
        if(finsetContent.find(MEANKEY) != finsetContent.end())
        {
            QString meanValue = finsetContent.value(MEANKEY).value.toString();
            QStringList meanList = meanValue.split(",");
            QString meanStr;
            for(int i = 0, iend = meanList.size(); i < iend; i++)
            {
                meanStr = meanStr + QString::number(meanList[i].toFloat(), 'f', 3) + ",";
            }
            m_mean = meanStr;
        }
        //THICK
        if(finsetContent.find(THICKKEY) != finsetContent.end())
        {
            QString thickValue = finsetContent.value(THICKKEY).value.toString();
            QStringList thickList = thickValue.split(",");
            QString thickStr;
            for(int i = 0, iend = thickList.size(); i < iend; i++)
            {
                thickStr = thickStr + QString::number(thickList[i].toFloat(), 'f', 3) + ",";
            }
            m_thick = thickStr;
        }
        //YUPPER
        if(finsetContent.find(YUPPERKEY) != finsetContent.end())
        {
            QString yupperValue = finsetContent.value(YUPPERKEY).value.toString();
            QStringList yupperList = yupperValue.split(",");
            QString yupperStr;
            for(int i = 0, iend = yupperList.size(); i < iend; i++)
            {
                yupperStr = yupperStr + QString::number(yupperList[i].toFloat(), 'f', 3) + ",";
            }
            m_yupper = yupperStr;
        }
        //YLOWER
        if(finsetContent.find(YLOWERKEY) != finsetContent.end())
        {
            QString ylowerValue = finsetContent.value(YLOWERKEY).value.toString();
            QStringList ylowerList = ylowerValue.split(",");
            QString ylowerStr;
            for(int i = 0, iend = ylowerList.size(); i < iend; i++)
            {
                ylowerStr = ylowerStr + QString::number(ylowerList[i].toFloat(), 'f', 3) + ",";
            }
            m_ylower = ylowerStr;
        }
    }
}

void FinsetChildTreeItem::setContentKey(const QString &key)
{
    m_key = key;
}
