#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T08:14:26
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_listentrytest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_listentrytest.cpp \
    ../../../MediaPlayer/src/Common/ListEntryImpl.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Common/ListEntryImpl.h \
    ../../../MediaPlayer/src/Common/Interfaces/ListEntry.h
