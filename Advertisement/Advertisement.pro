#-------------------------------------------------
#
# Project created by QtCreator 2013-12-13T22:08:23
#
#-------------------------------------------------

QT       += testlib network xml

QT       += gui

TARGET = tst_advertisementtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_advertisementtest.cpp \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementController.cpp \
    ../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.cpp \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementControllerImpl.cpp \
    AdvertisementRequestFakeImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.cpp \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.cpp \
    ../../../MediaPlayer/src/Network/RequestManager.cpp \
    ../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequestImpl.cpp \
    RequestManagerConnectionFakeImpl.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementController.h \
    ../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.h \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementControllerImpl.h \
    AdvertisementRequestFakeImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerImpl.h \
    ../../../MediaPlayer/src/Network/RequestManagerConnection.h \
    ../../../MediaPlayer/src/Network/RequestManager.h \
    ../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequestImpl.h \
    RequestManagerConnectionFakeImpl.h