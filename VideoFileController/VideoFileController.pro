#-------------------------------------------------
#
# Project created by QtCreator 2013-10-29T19:13:45
#
#-------------------------------------------------

QT       += sql testlib

QT       += gui

TARGET = tst_videofilecontrollertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../../../MediaPlayer/src/DB \
               ../../../MediaPlayer/src/Data/SqlModels \
               ../../../MediaPlayer/src/Data


SOURCES += tst_videofilecontrollertest.cpp \
    ../../../MediaPlayer/src/Controllers/Files/AbstractVideoFileController.cpp \
    ../../../MediaPlayer/src/Controllers/Files/VideoFileController.cpp \
    ../../../MediaPlayer/src/Data/MovieItemDataAccess.cpp \
    ../../../MediaPlayer/src/Data/SqlModels/VideoSqlTableModel.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Controllers/Files/AbstractVideoFileController.h \
    ../../../MediaPlayer/src/Controllers/Files/VideoFileController.h \
    ../../../MediaPlayer/src/Data/MovieItemDataAccess.h \
    ../../../MediaPlayer/src/Data/SqlModels/VideoSqlTableModel.h
