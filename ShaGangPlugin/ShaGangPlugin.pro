TEMPLATE = lib
CONFIG += plugin

QT += widgets

INCLUDEPATH += ../MainApp

TARGET = $$qtLibraryTarget(ShaGangPlugin)

DESTDIR = ../App/funcPlugins

HEADERS += \
    ShaGangPlugin.h

SOURCES += \
    ShaGangPlugin.cpp
