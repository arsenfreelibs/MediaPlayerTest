#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T16:47:53
#
#-------------------------------------------------# The application version
VERSION = 0.0.0.0

# Define the preprocessor macro to get the application version in our application.
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

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
