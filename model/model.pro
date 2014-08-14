#-------------------------------------------------
#
# Project created by QtCreator 2014-05-03T00:40:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY

SOURCES += \
    casetreemodel.cpp \
    modeltreeitem.cpp \
    treeitem.cpp \
    solutiontreeitem.cpp \
    fltcontreeitem.cpp \
    refqtreeitem.cpp \
    finsettreeitem.cpp \
    controltreeitem.cpp \
    deflcttreeitem.cpp \
    geometrytreeitem.cpp \
    protubtreeitem.cpp \
    trimtreeitem.cpp \
    inlettreeitem.cpp

HEADERS +=\
        model_global.h \
    casetreemodel.h \
    modeltreeitem.h \
    treeitem.h \
    solutiontreeitem.h \
    fltcontreeitem.h \
    casecontent.h \
    refqtreeitem.h \
    finsettreeitem.h \
    controltreeitem.h \
    deflcttreeitem.h \
    geometrytreeitem.h \
    protubtreeitem.h \
    trimtreeitem.h \
    inlettreeitem.h \
    propertyconstants.h

CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../libs/debug
    DLLDESTDIR = $$PWD/../debug
    DESTDIR = $$PWD/../libs/debug
    OBJECTS_DIR = $$PWD/debug/obj
    MOC_DIR = $$PWD/debug/moc
    UI_DIR = $$PWD/debug/ui
    RCC_DIR = $$PWD/debug/rcc
}else{
    LIBS += -L$$PWD/../libs/debug
    DLLDESTDIR = $$PWD/../debug
    DESTDIR = $$PWD/../libs/debug
    OBJECTS_DIR = $$PWD/release/obj
    MOC_DIR = $$PWD/release/moc
    UI_DIR = $$PWD/release/ui
    RCC_DIR = $$PWD/release/rcc
}
