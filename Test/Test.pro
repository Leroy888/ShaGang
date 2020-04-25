TEMPLATE = lib

CONFIG += plugin

TARGET = $$qtLibraryTarget(Test)

QT += widgets

INCLUDEPATH += ../MainApp

DESTDIR += ../App/funcPlugins

HEADERS += \
    TestPlugin.h

SOURCES += \
    TestPlugin.cpp
