#-------------------------------------------------
#
# Project created by QtCreator 2014-04-04T11:16:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = procwatcher
TEMPLATE = app


SOURCES += main.cpp\
        procwatcher.cpp \
    procfsmodel.cpp \
    procfs.cpp \
    procfsicons.cpp \
    procwatcherthread.cpp

HEADERS  += procwatcher.h \
    procfsmodel.h \
    procfs.h \
    procfsicons.h \
    procwatcherthread.h

FORMS    += procwatcher.ui
