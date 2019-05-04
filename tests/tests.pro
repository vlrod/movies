TEMPLATE = app

include(../defaults.pri)
QT += testlib
QT += network

CONFIG += console
CONFIG += c++14
CONFIG -= app_bundle
CONFIG += qt
CONFIG += testcase


SOURCES += tst_testomdbserviceapi.cpp

LIBS += -L../src -lmyapp

HEADERS += \
    webrequestfake.hpp



