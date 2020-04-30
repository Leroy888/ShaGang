#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T09:21:50
#
#-------------------------------------------------

QT       += widgets serialport network

TARGET = ShaGang
TEMPLATE = lib
DESTDIR = ../App/plugins

INCLUDEPATH += ./headers \
                ../MainApp


LIBS += $$PWD/GLWidget11.dll

DEFINES += CENTERWIDGETONE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Form.cpp \
    ShaGangInterface.cpp \
    clsSettings.cpp \
    com/Command.cpp \
    model/FileSaver.cpp \
    model/Lms5XX.cpp \
    model/SocketThread.cpp \
    model/TcpSocket.cpp \
    view/ClientForm.cpp \
    view/ControlForm.cpp \
    window.cpp

HEADERS +=\
        Form.h \
        ShaGangInterface.h \
        ShaGang_global.h \
        clsSettings.h \
        com/Command.h \
        model/DeviceFactory.h \
        model/DeviceModel.h \
        model/FileSaver.h \
        model/Lms5XX.h \
        model/SocketThread.h \
        model/TcpSocket.h \
        view/ClientForm.h \
        view/ControlForm.h \
        window.h
    
unix {
    target.path = /usr/lib
    INSTALLS += target
}
FORMS += \
    Form.ui \
    view/ClientForm.ui \
    view/ControlForm.ui

RESOURCES += \
    Res.qrc

