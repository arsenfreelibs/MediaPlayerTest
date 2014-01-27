#-------------------------------------------------
#
# Project created by QtCreator 2014-01-06T12:11:06
#
#-------------------------------------------------

QT       += testlib

QT       += gui

TARGET = tst_dropdownmodeltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_dropdownmodeltest.cpp \
    ../../../MediaPlayer/src/Data/TVModels/TVCategoryModel.cpp \
    ../../../MediaPlayer/src/Data/MoviesModels/MovieSortModels.cpp \
    ../../../MediaPlayer/src/Data/DropdownModel/DropdownModelBase.cpp


HEADERS += \
    ../../../MediaPlayer/src/Data/TVModels/TVCategoryModel.h \
    ../../../MediaPlayer/src/Data/MoviesModels/MovieSortModels.h \
    ../../../MediaPlayer/src/Data/DropdownModel/DropdownModelBase.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
