#-------------------------------------------------
#
# Project created by QtCreator 2015-12-17T16:10:44
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = auto_service_new
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cxx \
    database.cxx \
    owner.cxx \
    car.cxx \
    service.cxx

HEADERS += \
    database.hxx \
    owner.hxx \
    service.hxx \
    car.hxx \
    types.hxx
