#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T10:51:34
#
#-------------------------------------------------

QT       += sql testlib

QT       -= gui

TARGET = tst_tvfilecontrollertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src/DB \
               ../../../MediaPlayer/src/Data/SqlModels

SOURCES += tst_tvfilecontrollertest.cpp \
    ../../../MediaPlayer/src/Data/SqlModels/tvgidsqlmodel.cpp \
    ../../../MediaPlayer/src/Controllers/Files/TVFileController.cpp \
    ../../../MediaPlayer/src/Controllers/Files/AbstractTVFileController.cpp \
    ../../../MediaPlayer/src/DB/AbstractDBConnector.cpp \
    ../../../MediaPlayer/src/DB/DBConnector.cpp \
    ../../../MediaPlayer/src/Data/SqlModels/basesqltablemodel.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Data/SqlModels/tvgidsqlmodel.h \
    ../../../MediaPlayer/src/Controllers/Files/TVFileController.h \
    ../../../MediaPlayer/src/Controllers/Files/AbstractTVFileController.h \
    ../../../MediaPlayer/src/DB/AbstractDBConnector.h \
    ../../../MediaPlayer/src/DB/DBConnector.h \
    ../../../MediaPlayer/src/Data/SqlModels/basesqltablemodel.h
