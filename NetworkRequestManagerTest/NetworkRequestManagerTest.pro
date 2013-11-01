#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T12:12:14
#
#-------------------------------------------------

QT       += network testlib

TARGET = tst_networkrequestmanagertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src/DB \
               ../../../MediaPlayer/src/Data/SqlModels \
               ../../../MediaPlayer/src/Data \
               ../../../MediaPlayer/src/Protocol


SOURCES += tst_networkrequestmanagertest.cpp \
    ../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.cpp \
    ../../../MediaPlayer/src/Data/UserProfile.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.cpp \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.cpp \
    ../../../MediaPlayer/src/qt-json/json.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h \
    ../../../MediaPlayer/src/Data/UserProfile.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.h \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.h \
    ../../../MediaPlayer/src/qt-json/json.h
