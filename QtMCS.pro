#-------------------------------------------------
#
# Project created by QtCreator 2018-08-27T22:51:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtMCS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphitem.cpp \
    createconfig.cpp \
    config.cpp \
    _calculate.cpp

HEADERS  += mainwindow.h \
    graphitem.h \
    createconfig.h \
    config.h \
    calculate.h

FORMS    += mainwindow.ui \
    createconfig.ui \
    config.ui
