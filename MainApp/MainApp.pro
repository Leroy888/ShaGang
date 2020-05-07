#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T08:41:00
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainApp
TEMPLATE = app

INCLUDEPATH += ../ShaGang \
                /steel \
                ../SteelDll

LIBS += $$PWD/libs/Steel.dll

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



SOURCES += main.cpp\
        Executor.cpp \
        FormManager.cpp \
        JsonReader.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h \
    Executor.h \
    FormManager.h \
    FuncInterface.h \
    JsonReader.h \
    UiInterface.h

FORMS    += mainwindow.ui

DESTDIR = ../App

RESOURCES += \
    Res.qrc
