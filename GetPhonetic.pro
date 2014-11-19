#-------------------------------------------------
#
# Project created by QtCreator 2014-11-06T19:11:40
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GetPhonetic
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    translator.cpp

HEADERS  += mainwindow.h \
    translator.h

FORMS    += mainwindow.ui
