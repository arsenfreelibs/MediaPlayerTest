#-------------------------------------------------
#
# Project created by QtCreator 2014-02-22T14:15:37
#
#-------------------------------------------------

QT       += network testlib

QT       += gui

TARGET = tst_previewplaylistcontrollertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src/M3UParser

SOURCES += tst_previewplaylistcontrollertest.cpp \
    ../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.cpp \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.cpp \
    ../../../MediaPlayer/src/Data/UserProfile.cpp \
    ../../../MediaPlayer/src/qt-json/json.cpp \
    ../../../MediaPlayer/src/Data/PlaylistModel.cpp \
    ../../../MediaPlayer/src/Data/Settings.cpp \
    ../../../MediaPlayer/src/M3UParser/PDTParser.cpp \
    ../../../MediaPlayer/src/M3UParser/PDTEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/NDXParser.cpp \
    ../../../MediaPlayer/src/M3UParser/NDXEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/M3UParser.cpp \
    ../../../MediaPlayer/src/M3UParser/PlaylistEntry.cpp \
    ../../../MediaPlayer/src/M3UParser/Playlist.cpp \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/TitleListFilterProcessor.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/QualityListFilterProcessor.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntryDecorator.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntry.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListFilterProcessor.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/GenreListFilterProcessor.cpp \
    ../../../MediaPlayer/src/Data/TvModelCollections/FavoriteListFilterProcessor.cpp \
    ../../../MediaPlayer/src/Data/DropdownModel/TVModels/TVCategoryModel.cpp \
    ../../../MediaPlayer/src/Data/DropdownModel/DropdownModelBase.cpp \
    PlaylistModelFake.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Controllers/TV/PreviewPlaylistController.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.h \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.h \
    ../../../MediaPlayer/src/Data/UserProfile.h \
    ../../../MediaPlayer/src/qt-json/json.h \
    ../../../MediaPlayer/src/Data/PlaylistModel.h \
    ../../../MediaPlayer/src/Data/Settings.h \
    ../../../MediaPlayer/src/M3UParser/PDTParser.h \
    ../../../MediaPlayer/src/M3UParser/PDTEntry.h \
    ../../../MediaPlayer/src/M3UParser/NDXParser.h \
    ../../../MediaPlayer/src/M3UParser/NDXEntry.h \
    ../../../MediaPlayer/src/M3UParser/M3UParser.h \
    ../../../MediaPlayer/src/M3UParser/PlaylistEntry.h \
    ../../../MediaPlayer/src/M3UParser/Playlist.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/TitleListFilterProcessor.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/QualityListFilterProcessor.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntryDecorator.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListModelEntry.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/ListFilterProcessor.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/GenreListFilterProcessor.h \
    ../../../MediaPlayer/src/Data/TvModelCollections/FavoriteListFilterProcessor.h \
    ../../../MediaPlayer/src/Data/DropdownModel/TVModels/TVCategoryModel.h \
    ../../../MediaPlayer/src/Data/DropdownModel/DropdownModelBase.h \
    PlaylistModelFake.h
