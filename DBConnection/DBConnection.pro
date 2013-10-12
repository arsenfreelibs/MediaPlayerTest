#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T08:12:36
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_dbconnectiontest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_dbconnectiontest.cpp \
    ../../../MediaPlayer/src/DB/AbstractDBConnector.cpp \
    ../../../MediaPlayer/src/DB/DBConnector.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/DB/AbstractDBConnector.h \
    ../../../MediaPlayer/src/DB/DBConnector.h
