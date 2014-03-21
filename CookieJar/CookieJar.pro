#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T16:47:53
#
#-------------------------------------------------

QT       += network testlib

TARGET = tst_cookiejartest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_cookiejartest.cpp \
    ../../../MediaPlayer/src/Network/CookieJar.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../../MediaPlayer/src/Network/CookieJar.h
