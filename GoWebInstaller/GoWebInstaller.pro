#-------------------------------------------------
#
# Project created by QtCreator 2013-12-10T04:32:20
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# The application version
VERSION = 1.0.1
# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

TARGET = GoWebInstaller
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.cpp \
    ../../../MediaPlayer/src/Controllers/Update/UpdateController.cpp \
    ../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.cpp \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.cpp \
    ../../../MediaPlayer/src/Data/UserProfile.cpp \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequestImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManager.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloaderImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilder.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilderImpl.cpp \
    ../../../MediaPlayer/src/Network/FileDownloader/UrlDownloader.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.cpp

HEADERS  += mainwindow.h\
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadListener.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJob.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloader.h \
    ../../../MediaPlayer/src/Controllers/Update/UpdateController.h \
    ../../../MediaPlayer/src/Controllers/Update/UpdateControllerImpl.h \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequest.h \
    ../../../MediaPlayer/src/Data/UserProfile.h \
    ../../../MediaPlayer/src/Network/UpdateRequest/UpdateRequestImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.h \
    ../../../MediaPlayer/src/Network/RequestManager.h \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloaderImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilder.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/FileDownloadJobBuilderImpl.h \
    ../../../MediaPlayer/src/Network/FileDownloader/UrlDownloader.h \
    ../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.h

FORMS    += mainwindow.ui
