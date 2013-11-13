#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T20:25:33
#
#-------------------------------------------------

QT       += network testlib

QT       -= gui

TARGET = tst_updatecontrollertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_updatecontrollertest.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.cpp \
    ../../../MediaPlayer/src/Controllers/Update/UpdateController.cpp \
    ../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.cpp \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.cpp \
    FakeUpdateRequestSimpleImpl.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h \
    ../../../MediaPlayer/src/Controllers/Update/UpdateController.h \
    ../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h \
    FakeUpdateRequestSimpleImpl.h
