#-------------------------------------------------
#
# Project created by QtCreator 2014-02-20T04:51:22
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_playerpresettingtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_playerpresettingtest.cpp \
    ../../../MediaPlayer/src/Data/Settings.cpp \
    ../../../MediaPlayer/src/Controls/VLCPlayer/PreSettingVisitorImpl.cpp \
    PlayerPreSettableFakeImpl.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Controls/VLCPlayer/PreSettingVisitor.h \
    ../../../MediaPlayer/src/Controls/VLCPlayer/PlayerPreSettable.h \
    ../../../MediaPlayer/src/Data/Settings.h \
    ../../../MediaPlayer/src/Controls/VLCPlayer/PreSettingVisitorImpl.h \
    PlayerPreSettableFakeImpl.h
