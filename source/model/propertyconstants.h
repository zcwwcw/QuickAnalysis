#ifndef PROPERTYCONSTANTS_H
#define PROPERTYCONSTANTS_H

#include <QString>
#include <QStringList>
#include <QVariant>
#include <QHash>

enum PropertyType
{
    PROPERTY_TYPE_INVALID = 0,
    PROPERTY_TYPE_GROUP,
    PROPERTY_TYPE_ENUM,
    PROPERTY_TYPE_ENUM_GROUP,
    PROPERTY_TYPE_INT,
    PROPERTY_TYPE_DOUBLE,
    PROPERTY_TYPE_STRING,
    PROPERTY_TYPE_BOOL,
    PROPERTY_TYPE_STRING_REG
};

namespace PropertyConstants{
    static const QString PROPERTY_NAME = "name";
    static const QString PROPERTY_VALUE = "value";
    static const QString PROPERTY_VALUE_MIN = "min";
    static const QString PROPERTY_VALUE_MAX = "max";
    static const QString PROPERTY_VALUE_TYPE = "type";
    static const QString PROPERTY_SELECTABLE_VALUES = "selectableValues";
    static const QString PROPERTY_EDITABLE = "editable";
    static const QString PROPERTY_CHECKABLE = "checkable";
    static const QString PROPERTY_CHECKSTATE = "checkstate";
    static const QString PROPERTY_SUB_ITEMS = "subitems";
    static const QString PROPERTY_SHOW_TEXT = "showtext";
    static const QString PROPERTY_PATTERN = "pattern";
    static const QString CHILD_PROPERTY = "childProperty";
    static const QString PROPERTY_DECIMALS = "decimals";
}

#define INFINITYNUMBER 999999999

typedef QHash<QString, QVariant> PropertyItem;
inline PropertyItem getPropertyItem(const QString &name,
                                    const QString &showText,
                                    const PropertyType &type,
                                    const QVariant &value = QVariant(),
                                    const QVariant &min = QVariant(),
                                    const QVariant &max = QVariant(),
                                    const int &decimals = 1,
                                    const bool &checkAble = false,
                                    const Qt::CheckState &checkState = Qt::Unchecked,
                                    const QList<QVariant> &selectable = QList<QVariant>(),
                                    const bool &editable = true,
                                    const QString &pattern = QString())
{
    PropertyItem property;
    property.insert(PropertyConstants::PROPERTY_NAME, name);
    property.insert(PropertyConstants::PROPERTY_SHOW_TEXT, showText);
    property.insert(PropertyConstants::PROPERTY_VALUE_TYPE, type);
    property.insert(PropertyConstants::PROPERTY_VALUE, value);
    property.insert(PropertyConstants::PROPERTY_EDITABLE, editable);
    property.insert(PropertyConstants::PROPERTY_CHECKABLE, checkAble);
    property.insert(PropertyConstants::PROPERTY_CHECKSTATE, checkState);
    property.insert(PropertyConstants::PROPERTY_DECIMALS, decimals);

    if(!max.isNull())
        property.insert(PropertyConstants::PROPERTY_VALUE_MAX, max);

    if(!min.isNull())
        property.insert(PropertyConstants::PROPERTY_VALUE_MIN, min);

    if(!selectable.isEmpty())
        property.insert(PropertyConstants::PROPERTY_SELECTABLE_VALUES, selectable);

    if(!pattern.isEmpty())
        property.insert(PropertyConstants::PROPERTY_PATTERN, pattern);
    return property;
}

enum PatternType
{
    NINETY_TO_NEGATIVE_NINETY,
    INT_INFINITE_TO_ZERO,
    DECIMALS_LOW_HUNDRED_UP_ZERO,
    DECIMALS_INFINITE_TO_ZERO,
    DECIMALS_NO_LIMIT
};

inline QString getPattern(const PatternType &type, const int &count)
{
    QString pattern;
    switch(type)
    {
    case NINETY_TO_NEGATIVE_NINETY:
    {
        for(int i = 0, iend = count; i < iend; i++)
        {
            pattern.append("[-+]?[0-9]\\d{0,1},");
        }
        break;
    }
    case DECIMALS_LOW_HUNDRED_UP_ZERO:
    {
        for(int i = 0, iend = count; i < iend; i++)
        {
            pattern.append("[0-9]\\d{0,1}.[0-9]\\d{0,1},");
        }
        break;
    }
    case DECIMALS_INFINITE_TO_ZERO:
    {
        for(int i = 0, iend = count; i < iend; i++)
        {
            pattern.append("[0-9]\\d{0,9}.[0-9]\\d{0,1},");
        }
        break;
    }
    case DECIMALS_NO_LIMIT:
    {
        for(int i = 0, iend = count; i < iend; i++)
        {
            pattern.append("\\d+.[0-9]\\d{0,1},");
        }
        break;
    }
    case INT_INFINITE_TO_ZERO:
    {
        for(int i = 0, iend = count; i < iend; i++)
        {
            pattern.append("\\d+.");
        }
    }
    }
    return pattern;
}

inline QVariant setNewContent(QVariant oriData, int setCount, QString appendStr)
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

inline bool getBoolValue(const QString value)
{
    if(value == "True")
    {
        return true;
    }
    else
    {
        return false;
    }
}

#endif // PROPERTYCONSTANTS_H
