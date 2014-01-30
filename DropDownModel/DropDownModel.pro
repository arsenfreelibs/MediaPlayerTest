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
    ../../../MediaPlayer/src/Data/DropdownModel/TVModels/TVCategoryModel.cpp \
    ../../../MediaPlayer/src/Data/DropdownModel/MoviesModels/MovieSortModels.cpp \
    ../../../MediaPlayer/src/Data/DropdownModel/DropdownModelBase.cpp

HEADERS += \
    ../../../MediaPlayer/src/Data/DropdownModel/TVModels/TVCategoryModel.h \
    ../../../MediaPlayer/src/Data/DropdownModel/MoviesModels/MovieSortModels.h \
    ../../../MediaPlayer/src/Data/DropdownModel/DropdownModelBase.h
DEFINES += SRCDIR=\\\"$$PWD/\\\"
