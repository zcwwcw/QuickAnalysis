#include "propertydockwidget.h"

PropertyDockWidget::PropertyDockWidget(QWidget *parent) :
    QDockWidget(tr("Property Widget"), parent)
{
    initUI();
    initManager();
}

void PropertyDockWidget::showProperties(QString objectName, QList<QVariant> property)
{
    setWindowTitle(objectName + tr(" Property"));
    clear();
    if(!property.isEmpty())
    {
        for(int i = 0, iend = property.count(); i < iend; i++)
        {
            QHash<QString, QVariant> childProperty = property[i].toHash();
            if(childProperty.isEmpty())
            {
                continue;
            }
            QtProperty *item = addProperty(childProperty);
            m_treePropertyBroswer->addProperty(item);
        }
    }
}

void PropertyDockWidget::updateProperties(QString objectName, QList<QVariant> property)
{
    setWindowTitle(objectName + tr(" Property"));
    if(!property.isEmpty())
    {
        for(int i = 0, iend = property.count(); i < iend; i++)
        {
            QHash<QString, QVariant> childProperty = property[i].toHash();
            if(childProperty.isEmpty())
            {
                continue;
            }
            updateProperty(childProperty);
        }
    }
}

void PropertyDockWidget::broswerDataChanged(QtProperty *property)
{
    QString value = property->valueText();
    QString propertyKey = m_propertyToKey.value(property);
    if(property->isCheckable())
    {
        emit propertyCheckStateChanged(propertyKey, property->checkState());
    }
    emit propertyDataChanged(propertyKey, value);
}

void PropertyDockWidget::initUI()
{
    m_treePropertyBroswer = new QtTreePropertyBrowser(this);
    connect(m_treePropertyBroswer, SIGNAL(dataChanged(QtProperty*)),
            this, SLOT(broswerDataChanged(QtProperty*)));
    this->setWidget(m_treePropertyBroswer);
}

void PropertyDockWidget::initManager()
{
    //init manager
    m_intManager = new QtIntPropertyManager(this);
    m_doubleManager = new QtDoublePropertyManager(this);
    m_stringManager = new QtStringPropertyManager(this);
    m_enumManager = new QtEnumPropertyManager(this);
    m_boolManager = new QtBoolPropertyManager(this);
    m_groupManager = new QtGroupPropertyManager(this);

    //init editor fac
    QtDoubleSpinBoxFactory *doubleEditorFac = new QtDoubleSpinBoxFactory(this);
    QtSpinBoxFactory *intEditorFac = new QtSpinBoxFactory(this);
    QtEnumEditorFactory *enumEditorFac = new QtEnumEditorFactory(this);
    QtLineEditFactory *stringEditorFac = new QtLineEditFactory(this);
    QtCheckBoxFactory *boolEditorFac = new QtCheckBoxFactory(this);

    //set fac for manager
    m_treePropertyBroswer->setFactoryForManager(m_intManager, intEditorFac);
    m_treePropertyBroswer->setFactoryForManager(m_doubleManager, doubleEditorFac);
    m_treePropertyBroswer->setFactoryForManager(m_stringManager, stringEditorFac);
    m_treePropertyBroswer->setFactoryForManager(m_enumManager, enumEditorFac);
    m_treePropertyBroswer->setFactoryForManager(m_boolManager, boolEditorFac);
}

void PropertyDockWidget::clear()
{
    m_propertyToKey.clear();
    m_keyToProperty.clear();
    QList<QtProperty*> treeTopProps = m_treePropertyBroswer->properties();
    QList<QtProperty*>::iterator treeItProp = treeTopProps.begin();
    while(treeItProp != treeTopProps.end())
    {
        delete *treeItProp;
        treeItProp++;
    }
}

QtProperty *PropertyDockWidget::addProperty(const QHash<QString, QVariant> &property)
{
    QtProperty *item = NULL;
    QString propertyName = property.value(PropertyConstants::PROPERTY_NAME).toString();
    QString showText = property.value(PropertyConstants::PROPERTY_SHOW_TEXT).toString();
    QVariant value = property.value(PropertyConstants::PROPERTY_VALUE);

    switch(property.value(PropertyConstants::PROPERTY_VALUE_TYPE).toInt())
    {
        case PROPERTY_TYPE_INT:
        {
            item = m_intManager->addProperty(showText);
            m_intManager->setValue(item, value.toInt());

            QVariant min = property.value(PropertyConstants::PROPERTY_VALUE_MIN);
            QVariant max = property.value(PropertyConstants::PROPERTY_VALUE_MAX);

            if( min.isValid() && max.isValid())
            {
                m_intManager->setMinimum(item, min.toInt());
                m_intManager->setMaximum(item, max.toInt());
            }
            m_intManager->setSingleStep(item, 1);
            break;
        }
        case PROPERTY_TYPE_DOUBLE:
        {
            item = m_doubleManager->addProperty(showText);
            m_doubleManager->setValue(item, value.toDouble());
            QVariant min = property.value(PropertyConstants::PROPERTY_VALUE_MIN);
            QVariant max = property.value(PropertyConstants::PROPERTY_VALUE_MAX);
            QVariant decimals = property.value(PropertyConstants::PROPERTY_DECIMALS);
            if( min.isValid() && max.isValid())
            {
                m_doubleManager->setMinimum(item, min.toDouble());
                m_doubleManager->setMaximum(item, max.toDouble());
            }
            float step = 1;
            for(int i = 0, iend = decimals.toInt(); i < iend; i++)
            {
                step = step/10;
            }
            m_doubleManager->setSingleStep(item, step);
            m_doubleManager->setDecimals(item, decimals.toInt());
            break;
        }
        case PROPERTY_TYPE_STRING:
        {
            item = m_stringManager->addProperty(showText);
            m_stringManager->setValue(item, value.toString());
            break;
        }
        case PROPERTY_TYPE_BOOL:
        {
            item = m_boolManager->addProperty(showText);
            m_boolManager->setValue(item, value.toBool());
            break;
        }
        case PROPERTY_TYPE_STRING_REG:
        {
            item = m_stringManager->addProperty(showText);
            QString pattern = property.value(PropertyConstants::PROPERTY_PATTERN).toString();
            m_stringManager->setRegExp(item, QRegExp(pattern));
            m_stringManager->setValue(item, value.toString());
            break;
        }
        case PROPERTY_TYPE_ENUM:
        {
            item = m_enumManager->addProperty(showText);
            QList<QVariant> values = property.value(PropertyConstants::PROPERTY_SELECTABLE_VALUES).toList();
            QStringList enumNames;
            for(int i = 0, iend = values.count(); i < iend; i++)
            {
                enumNames.append(values[i].toString());
            }
            m_enumManager->setEnumNames(item, enumNames);
            m_enumManager->setValue(item, value.toInt());
            break;
        }
        case PROPERTY_TYPE_ENUM_GROUP:
        {
            item = m_enumManager->addProperty(showText);
            QList<QVariant> values = property.value(PropertyConstants::PROPERTY_SELECTABLE_VALUES).toList();
            QStringList enumNames;
            for(int i = 0, iend = values.count(); i < iend; i++)
            {
                enumNames.append(values[i].toString());
            }
            m_enumManager->setEnumNames(item, enumNames);
            m_enumManager->setValue(item, value.toInt());

            QList<QVariant> childProperties = property.value(PropertyConstants::CHILD_PROPERTY).toList();
            foreach(QVariant property, childProperties)
            {
                QHash<QString, QVariant> childProperty = property.toHash();
                if(childProperty.isEmpty())
                {
                    continue;
                }
                QtProperty *childItem = addProperty(childProperty);
                item->addSubProperty(childItem);
            }
            break;
        }
        case PROPERTY_TYPE_GROUP:
        {
            item = m_groupManager->addProperty(showText);
            QList<QVariant> childProperties = property.value(PropertyConstants::CHILD_PROPERTY).toList();
            foreach(QVariant property, childProperties)
            {
                QHash<QString, QVariant> childProperty = property.toHash();
                if(childProperty.isEmpty())
                {
                    continue;
                }
                QtProperty *childItem = addProperty(childProperty);
                item->addSubProperty(childItem);
            }
            break;
        }
        case PROPERTY_TYPE_BOOL_GROUP:
        {
            item = m_boolManager->addProperty(showText);
            m_boolManager->setValue(item, value.toBool());
            QList<QVariant> childProperties = property.value(PropertyConstants::CHILD_PROPERTY).toList();
            foreach(QVariant property, childProperties)
            {
                QHash<QString, QVariant> childProperty = property.toHash();
                if(childProperty.isEmpty())
                {
                    continue;
                }
                QtProperty *childItem = addProperty(childProperty);
                item->addSubProperty(childItem);
            }
            break;
        }
        default:
            break;
    }
    QVariant editable = property.value(PropertyConstants::PROPERTY_EDITABLE);
    if(!editable.isNull())
    {
        item->setEnabled(editable.toBool());
    }
    QVariant checkable = property.value(PropertyConstants::PROPERTY_CHECKABLE);
    if(!checkable.isNull())
    {
        item->setCheckable(checkable.toBool());
    }
    QVariant checkState = property.value(PropertyConstants::PROPERTY_CHECKSTATE);
    if(!checkState.isNull())
    {
        item->setCheckState((Qt::CheckState)checkState.toInt());
    }
    m_propertyToKey.insert(item, propertyName);
    m_keyToProperty.insert(propertyName, item);
    return item;
}

void PropertyDockWidget::updateProperty(const QHash<QString, QVariant> &property)
{
    QString propertyName = property.value(PropertyConstants::PROPERTY_NAME).toString();
    QVariant value = property.value(PropertyConstants::PROPERTY_VALUE);
    if(m_keyToProperty.find(propertyName) == m_keyToProperty.end())
    {
        return;
    }
    QtProperty *item = m_keyToProperty.value(propertyName);

    switch(property.value(PropertyConstants::PROPERTY_VALUE_TYPE).toInt())
    {
        case PROPERTY_TYPE_INT:
        {
            m_intManager->setValue(item, value.toInt());
            break;
        }
        case PROPERTY_TYPE_DOUBLE:
        {
            m_doubleManager->setValue(item, value.toDouble());
            break;
        }
        case PROPERTY_TYPE_STRING:
        {
            m_stringManager->setValueWithUpdate(item, value.toString());
            break;
        }
        case PROPERTY_TYPE_BOOL:
        {
            m_boolManager->setValue(item, value.toBool());
            break;
        }
        case PROPERTY_TYPE_STRING_REG:
        {
            QString pattern = property.value(PropertyConstants::PROPERTY_PATTERN).toString();
            m_stringManager->setRegExp(item, QRegExp(pattern));
            m_stringManager->setValue(item, value.toString());
            break;
        }
        case PROPERTY_TYPE_ENUM:
        {
            m_enumManager->setValue(item, value.toInt());
            break;
        }
        case PROPERTY_TYPE_ENUM_GROUP:
        {
            m_enumManager->setValue(item, value.toInt());
            QList<QVariant> childProperties = property.value(PropertyConstants::CHILD_PROPERTY).toList();
            foreach(QVariant property, childProperties)
            {
                QHash<QString, QVariant> childProperty = property.toHash();
                if(childProperty.isEmpty())
                {
                    continue;
                }
                updateProperty(childProperty);
            }
            break;
        }
        case PROPERTY_TYPE_GROUP:
        {
            QList<QVariant> childProperties = property.value(PropertyConstants::CHILD_PROPERTY).toList();
            foreach(QVariant property, childProperties)
            {
                QHash<QString, QVariant> childProperty = property.toHash();
                if(childProperty.isEmpty())
                {
                    continue;
                }
                updateProperty(childProperty);
            }
            break;
        }
        case PROPERTY_TYPE_BOOL_GROUP:
        {
            m_boolManager->setValue(item, value.toBool());
            QList<QVariant> childProperties = property.value(PropertyConstants::CHILD_PROPERTY).toList();
            foreach(QVariant property, childProperties)
            {
                QHash<QString, QVariant> childProperty = property.toHash();
                if(childProperty.isEmpty())
                {
                    continue;
                }
                updateProperty(childProperty);
            }
            break;
        }
        default:
            break;
    }
    QVariant editable = property.value(PropertyConstants::PROPERTY_EDITABLE);
    if(!editable.isNull())
    {
        item->setEnabled(editable.toBool());
    }
    QVariant checkable = property.value(PropertyConstants::PROPERTY_CHECKABLE);
    if(!checkable.isNull())
    {
        item->setCheckable(checkable.toBool());
    }
    QVariant checkState = property.value(PropertyConstants::PROPERTY_CHECKSTATE);
    if(!checkState.isNull())
    {
        item->setCheckState((Qt::CheckState)checkState.toInt());
    }
    m_treePropertyBroswer->update();
}
