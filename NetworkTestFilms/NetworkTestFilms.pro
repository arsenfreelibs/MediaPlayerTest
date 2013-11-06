#-------------------------------------------------
#
# Project created by QtCreator 2013-11-06T04:42:22
#
#-------------------------------------------------

QT       += core network

QT       += gui

TARGET = NetworkTestFilms
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.cpp \
    ../../../MediaPlayer/src/Data/UserProfile.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.cpp \
    ../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.cpp \
    ../../../MediaPlayer/src/qt-json/json.cpp \
    NetworkFilmProtocolTester.cpp \
    NetworkFileRequestManager.cpp \
    FileFilmDownloader.cpp

HEADERS += \
    ../../../MediaPlayer/src/Data/UserProfile.h \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.h \
    ../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h \
    ../../../MediaPlayer/src/qt-json/json.h \
    NetworkFilmProtocolTester.h \
    NetworkFileRequestManager.h \
    FileFilmDownloader.h
