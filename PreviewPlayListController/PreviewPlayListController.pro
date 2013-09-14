#-------------------------------------------------
#
# Project created by QtCreator 2013-09-14T17:34:54
#
#-------------------------------------------------

QT       += testlib
QT       += gui
QT       += network

TARGET = tst_previewplaylistcontrollertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src
INCLUDEPATH += ../../../MediaPlayer/src/Data
INCLUDEPATH += ../../../MediaPlayer/src/Protocol
INCLUDEPATH += ../../../MediaPlayer/src/M3UParser
INCLUDEPATH += ../../../MediaPlayer/src/Controllers/TV


SOURCES += tst_previewplaylistcontrollertest.cpp\
    ../../../MediaPlayer/src/Data/PlaylistModel.cpp \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/PlaylistEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/Playlist.cpp \
    ../../../MediaPlayer/src/M3UParser/PDTParser.cpp \
    ../../../MediaPlayer/src/M3UParser/PDTEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/NDXParser.cpp \
    ../../../MediaPlayer/src/M3UParser/NDXEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/M3UParser.cpp \
    ../../../MediaPlayer/src/qt-json/json.cpp
#    ../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.cpp \
#    ../../../MediaPlayer/src/Controllers/TV/TVGuideProgramsController.cpp \
#    ../../../src/Protocol/NetworkRequestManagerConnection.cpp \
#    ../../../src/Protocol/NetworkRequestManager.cpp


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
    ../../../MediaPlayer/src/qt-json/json.h
#    ../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.h \
#    ../../../MediaPlayer/src/Controllers/TV/TVGuideProgramsController.h \
#    ../../../src/Protocol/NetworkRequestManagerConnection.h \
#    ../../../src/Protocol/NetworkRequestManager.h
