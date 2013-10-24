#-------------------------------------------------
#
# Project created by QtCreator 2013-08-24T10:33:51
#
#-------------------------------------------------

QT       += testlib
QT       += gui

TARGET = tst_playlistmodeltesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src
INCLUDEPATH += ../../../MediaPlayer/src/M3UParser
INCLUDEPATH += ../../../MediaPlayer/src/Data

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
    tst_playlistmodeltest.cpp \
    ../../../MediaPlayer/src/qt-json/json.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntry.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntryDecorator.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListFilterProcessor.cpp

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
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntry.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntryDecorator.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListFilterProcessor.h
