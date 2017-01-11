#-------------------------------------------------
#
# Project created by QtCreator 2016-11-14T15:15:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AlarmViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    nsalarmmodel.cpp

HEADERS  += mainwindow.h \
    alarmform.h \
    nsalarmmodel.h

FORMS    += \
    mainwindow.ui

RC_FILE = AlarmViewer.rc
