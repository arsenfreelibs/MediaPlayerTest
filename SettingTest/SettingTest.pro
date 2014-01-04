#-------------------------------------------------
#
# Project created by QtCreator 2014-01-04T09:59:43
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_settingtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += TEST_ENV


SOURCES += tst_settingtest.cpp \
    ../../../MediaPlayer/src/Data/Settings.cpp

HEADERS += \
    ../../../MediaPlayer/src/Data/Settings.h

DEFINES += SRCDIR=\\\"$$PWD/\\\"
