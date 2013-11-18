#-------------------------------------------------
#
# Project created by QtCreator 2013-11-02T07:43:54
#
#-------------------------------------------------

QT       += core network

QT       += gui

TARGET = NetworkTest
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
    NetworkProtocolTester.cpp \
    FileDownloader.cpp \
    torrent/trackerclient.cpp \
    torrent/torrentserver.cpp \
    torrent/torrentclient.cpp \
    torrent/ratecontroller.cpp \
    torrent/peerwireclient.cpp \
    torrent/metainfo.cpp \
    torrent/filemanager.cpp \
    torrent/connectionmanager.cpp \
    torrent/bencodeparser.cpp \
    TorrentFileDownloader.cpp

HEADERS += \
    ../../../MediaPlayer/src/Data/UserProfile.h \
    ../../../MediaPlayer/src/Data/PlaylistModelEntry.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManagerConnection.h \
    ../../../MediaPlayer/src/Protocol/NetworkRequestManager.h \
    ../../../MediaPlayer/src/Protocol/BaseNetworkRequestManager.h \
    ../../../MediaPlayer/src/qt-json/json.h \
    NetworkProtocolTester.h \
    FileDownloader.h \
    torrent/trackerclient.h \
    torrent/torrentserver.h \
    torrent/torrentclient.h \
    torrent/ratecontroller.h \
    torrent/peerwireclient.h \
    torrent/metainfo.h \
    torrent/filemanager.h \
    torrent/connectionmanager.h \
    torrent/bencodeparser.h \
    TorrentFileDownloader.h
