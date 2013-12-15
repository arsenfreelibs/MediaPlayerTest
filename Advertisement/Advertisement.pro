#-------------------------------------------------
#
# Project created by QtCreator 2013-12-13T22:08:23
#
#-------------------------------------------------

QT       += testlib

QT       += gui

TARGET = tst_advertisementtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_advertisementtest.cpp \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementController.cpp \
    ../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.cpp \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementControllerImpl.cpp \
    AdvertisementRequestFakeImpl.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementController.h \
    ../../../MediaPlayer/src/Network/AdvertisementRequest/AdvertisementRequest.h \
    ../../../MediaPlayer/src/Controllers/Advertisement/AdvertisementControllerImpl.h \
    AdvertisementRequestFakeImpl.h
