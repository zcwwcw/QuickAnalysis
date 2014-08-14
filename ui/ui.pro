#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T23:53:26
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuickAnalysis
TEMPLATE = app

INCLUDEPATH += $$PWD/../Model \
               $$PWD/../Project \
               $$PWD/../qtpropertybrowser \
               $$PWD/../qwt

SOURCES += main.cpp\
        mainwindow.cpp \
    propertydockwidget.cpp \
    centralwidget.cpp \
    myglwidget.cpp \
    casetreeview.cpp

HEADERS  += mainwindow.h \
    propertydockwidget.h \
    centralwidget.h \
    myglwidget.h \
    casetreeview.h

CONFIG(debug, debug|release){
    LIBS += -L$$PWD/../libs/debug -lmodel -lqtpropertybrowser -lqwt
    DESTDIR = $$PWD/../debug
    OBJECTS_DIR = $$PWD/debug/obj
    MOC_DIR = $$PWD/debug/moc
    UI_DIR = $$PWD/debug/ui
    RCC_DIR = $$PWD/debug/rcc
}else{
    LIBS += -L$$PWD/../libs/debug -lmodel -lqtpropertybrowser -lqwt
    DESTDIR = $$PWD/../debug
    OBJECTS_DIR = $$PWD/release/obj
    MOC_DIR = $$PWD/release/moc
    UI_DIR = $$PWD/release/ui
    RCC_DIR = $$PWD/release/rcc
}

RESOURCES += \
    src.qrc

FORMS +=
