#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T19:45:21
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_broadcastertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_broadcastertest.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.cpp \
    ../../../MediaPlayer/src/Common/ListEntryImpl.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModel.h \
    ../../../MediaPlayer/src/Common/ListEntryImpl.h \
    ../../../MediaPlayer/src/Common/Interfaces/ListEntry.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.h
