#ifndef PROPERTYDOCKWIDGET_H
#define PROPERTYDOCKWIDGET_H

#include <QDockWidget>
#include <QDate>
#include <QLocale>
#include "qteditorfactory.h"
#include "propertyconstants.h"
#include "qttreepropertybrowser.h"
#include "qtpropertymanager.h"
#include "qtvariantproperty.h"
#include "qttreepropertybrowser.h"

class PropertyDockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit PropertyDockWidget(QWidget *parent = 0);
public slots:
    void showProperties(QString objectName, QList<QVariant> property);

    void updateProperties(QString objectName, QList<QVariant> property);
signals:
    void propertyDataChanged(QString propertyKey, QString value);

    void propertyCheckStateChanged(QString propertyKey, Qt::CheckState state);
private slots:
    void broswerDataChanged(QtProperty *property);
private:
    void initUI();

    void initManager();

    void clear();

    QtProperty *addProperty(const QHash<QString, QVariant> &property);

    void updateProperty(const QHash<QString, QVariant> &property);
private:
    QHash<QtProperty *, QString> m_propertyToKey;
    QHash<QString, QtProperty *> m_keyToProperty;

    QtTreePropertyBrowser *m_treePropertyBroswer;

    //property manager
    QtIntPropertyManager *m_intManager;
    QtDoublePropertyManager *m_doubleManager;
    QtStringPropertyManager *m_stringManager;
    QtEnumPropertyManager *m_enumManager;
    QtBoolPropertyManager *m_boolManager;
    QtGroupPropertyManager *m_groupManager;
};

#endif // PROPERTYDOCKWIDGET_H
