#-------------------------------------------------
#
# Project created by QtCreator 2014-05-15T19:45:21
#
#-------------------------------------------------

VERSION = 0.0.0.0

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QT       += testlib network sql

QT       -= gui

TARGET = tst_broadcastertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_broadcastertest.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.cpp \
    ../../../MediaPlayer/src/Common/ListEntryImpl.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.cpp \
    ../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterControllerImpl.cpp \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequest.cpp \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequestImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Network/RequestManager.cpp \
    ../UpdateController/RequestManagerConnectionFakeImpl.cpp \
    ../../../MediaPlayer/src/Data/Settings.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterSqlTableModel.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelInfoImpl.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterInfoModelView.cpp \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterInfo.cpp \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterInfoRequestImpl.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelImpl.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelEntry.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModel.h \
    ../../../MediaPlayer/src/Common/ListEntryImpl.h \
    ../../../MediaPlayer/src/Common/Interfaces/ListEntry.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelView.h \
    ../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterControllerImpl.h \
    ../../../MediaPlayer/src/Controllers/Broadcaster/BroadcasterController.h \
    ../../../MediaPlayer/src/Common/Statuses/RequestStatuses.h \
    ../../../MediaPlayer/src/Common/Statuses/ControllerStatuses.h \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequest.h \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterRequestImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerConnectionImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.h \
    ../../../MediaPlayer/src/Network/RequestManager.h \
    ../UpdateController/RequestManagerConnectionFakeImpl.h \
    ../../../MediaPlayer/src/Data/Settings.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterSqlTableModel.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelInfoImpl.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterModelInfo.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterInfoModelView.h \
    ../../../MediaPlayer/src/Data/Broadcaster/BroadcasterInfo.h \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterInfoRequestImpl.h \
    ../../../MediaPlayer/src/Network/BroadcasterRequest/BroadcasterInfoRequest.h
