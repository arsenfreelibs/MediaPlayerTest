#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T14:15:37
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

TARGET = tst_previewplaylistcontrollertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_previewplaylistcontrollertest.cpp \
    ../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.h
