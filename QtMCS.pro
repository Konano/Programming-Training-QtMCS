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
    config.cpp \
    graphitem.cpp

HEADERS  += mainwindow.h \
    config.h \
    graphitem.h

FORMS    += mainwindow.ui \
    config.ui
