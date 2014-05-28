#-------------------------------------------------
#
# Project created by QtCreator 2014-02-23T23:49:47
#
#-------------------------------------------------

QT       += core gui

TARGET = qtpropertybrowser
TEMPLATE = lib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += QT_QTPROPERTYBROWSER_EXPORT
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

SOURCES += $$PWD/qtpropertybrowser.cpp \
        $$PWD/qtpropertymanager.cpp \
        $$PWD/qteditorfactory.cpp \
        $$PWD/qtvariantproperty.cpp \
        $$PWD/qttreepropertybrowser.cpp \
        $$PWD/qtbuttonpropertybrowser.cpp \
        $$PWD/qtgroupboxpropertybrowser.cpp \
        $$PWD/qtpropertybrowserutils.cpp
HEADERS += $$PWD/qtpropertybrowser.h \
        $$PWD/qtpropertymanager.h \
        $$PWD/qteditorfactory.h \
        $$PWD/qtvariantproperty.h \
        $$PWD/qttreepropertybrowser.h \
        $$PWD/qtbuttonpropertybrowser.h \
        $$PWD/qtgroupboxpropertybrowser.h \
        $$PWD/qtpropertybrowserutils_p.h
RESOURCES += $$PWD/qtpropertybrowser.qrc

CONFIG(debug, debug|release){
    DLLDESTDIR = $$PWD/../debug
    DESTDIR = $$PWD/../libs/debug
    OBJECTS_DIR = $$PWD/debug/obj
    MOC_DIR = $$PWD/debug/moc
    UI_DIR = $$PWD/debug/ui
    RCC_DIR = $$PWD/debug/rcc
}else{
    DLLDESTDIR = $$PWD/../debug
    DESTDIR = $$PWD/../libs/debug
    OBJECTS_DIR = $$PWD/release/obj
    MOC_DIR = $$PWD/release/moc
    UI_DIR = $$PWD/release/ui
    RCC_DIR = $$PWD/release/rcc
}
