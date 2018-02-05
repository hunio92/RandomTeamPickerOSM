#-------------------------------------------------
#
# Project created by QtCreator 2018-01-31T13:27:53
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RandomTeamPicker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Leagues.cpp

HEADERS  += mainwindow.h \
    Leagues.h

FORMS    += mainwindow.ui
