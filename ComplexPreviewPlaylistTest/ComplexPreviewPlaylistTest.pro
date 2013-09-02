#-------------------------------------------------
#
# Project created by QtCreator 2013-08-29T17:51:22
#
#-------------------------------------------------
TARGET = tst_complexpreviewplaylisttest

QT       += network testlib
QT       += gui
QT += gui-private widgets


CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src
INCLUDEPATH += ../../../MediaPlayer/src/M3UParser
INCLUDEPATH += ../../../MediaPlayer/src/Protocol

SOURCES += \
    ../../../MediaPlayer/src/Data/PlaylistModel.cpp \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/PlaylistEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/Playlist.cpp \
    ../../../MediaPlayer/src/M3UParser/PDTParser.cpp \
    ../../../MediaPlayer/src/M3UParser/PDTEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/NDXParser.cpp \
    ../../../MediaPlayer/src/M3UParser/NDXEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/M3UParser.cpp \
    tst_complexpreviewplaylisttest.cpp \
    ../../../MediaPlayer/src/qt-json/json.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.cpp \
    ../../../MediaPlayer/src/Utils/ErrorReporter.cpp \
    ../../../MediaPlayer/src/Data/UserProfile.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.h \
    ../../../MediaPlayer/src/Data/PlaylistModel.h \
    ../../../MediaPlayer/src/M3UParser/PlaylistEntry.h \
    ../../../MediaPlayer/src/M3UParser/Playlist.h \
    ../../../MediaPlayer/src/M3UParser/PDTParser.h \
    ../../../MediaPlayer/src/M3UParser/PDTEntry.h \
    ../../../MediaPlayer/src/M3UParser/NDXParser.h \
    ../../../MediaPlayer/src/M3UParser/NDXEntry.h \
    ../../../MediaPlayer/src/M3UParser/M3UParser.h \
    ../../../MediaPlayer/src/qt-json/json.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.h \
    ../../../MediaPlayer/src/Utils/ErrorReporter.h \
    ../../../MediaPlayer/src/Data/UserProfile.h
