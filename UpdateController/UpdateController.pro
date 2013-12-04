#-------------------------------------------------
#
# Project created by QtCreator 2013-11-12T20:25:33
#
#-------------------------------------------------

QT       += network testlib

QT       += gui

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
    FakeUpdateRequestSimpleImpl.cpp \
    ../../../MediaPlayer/src/Data/UserProfile.cpp \
    FileDownloaderFakeImpl.cpp \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequestImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManager.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.cpp \
    RequestManagerConnectionFakeImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloaderImpl.cpp \
    FileDownloaderTestFakeImpl.cpp \
    FileDownloadJobBuilderFakeImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilder.cpp \
    FileDownloadJobFakeImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilderImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/UrlDownloader.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"\
           VERSION_APP=\\\"1.0.1\\\"

HEADERS += \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h \
    ../../../MediaPlayer/src/Controllers/Update/UpdateController.h \
    ../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h \
    FakeUpdateRequestSimpleImpl.h \
    ../../../MediaPlayer/src/Data/UserProfile.h \
    FileDownloaderFakeImpl.h \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequestImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.h \
    ../../../MediaPlayer/src/Network/RequestManager.h \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.h \
    RequestManagerConnectionFakeImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloaderImpl.h \
    FileDownloaderTestFakeImpl.h \
    FileDownloadJobBuilderFakeImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilder.h \
    FileDownloadJobFakeImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilderImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/UrlDownloader.h
