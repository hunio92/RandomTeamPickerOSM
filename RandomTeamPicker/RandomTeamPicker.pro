#-------------------------------------------------
#
# Project created by QtCreator 2018-01-31T13:27:53
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RandomTeamPicker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp

HEADERS  += mainwindow.h \
    dbmanager.h

FORMS    += mainwindow.ui

RESOURCES += \
    resource.qrc
