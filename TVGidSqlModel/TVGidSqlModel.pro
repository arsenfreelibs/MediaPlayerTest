#-------------------------------------------------
#
# Project created by QtCreator 2013-10-10T05:01:05
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_tvgidsqlmodeltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tvgidsqlmodeltest.cpp \
    ../../../MediaPlayer/src/Data/SqlModels/tvgidsqlmodel.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Data/SqlModels/tvgidsqlmodel.h
