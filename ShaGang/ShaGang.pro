#-------------------------------------------------
#
# Project created by QtCreator 2020-05-06
#
#-------------------------------------------------

QT       += widgets serialport network

TARGET = ShaGang
TEMPLATE = lib
DESTDIR = ../App/plugins

INCLUDEPATH += ./include \
                ../MainApp


LIBS += $$PWD/libs/GLWidget.dll

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
    ShaGangInterface.cpp \
    clsSettings.cpp \
    com/Command.cpp \
    model/FileSaver.cpp \
    model/JsonReader.cpp \
    model/LRSxxFileThread.cpp \
    model/Lms5XX.cpp \
    model/SerialPort.cpp \
    model/SocketThread.cpp \
    model/TcpSocket.cpp \
    view/ClientForm.cpp \
    view/ControlForm.cpp \
    view/DataForm.cpp \
    view/DataWidget.cpp \
    view/DockWidget.cpp \
    view/MainForm.cpp \
    view/ScrollArea.cpp \
    view/Widget.cpp \
    window.cpp

HEADERS +=\
        ShaGangInterface.h \
        ShaGang_global.h \
        clsSettings.h \
        com/Command.h \
        model/DeviceFactory.h \
        model/DeviceModel.h \
        model/FileSaver.h \
        model/JsonReader.h \
        model/LRSxxFileThread.h \
        model/Lms5XX.h \
        model/SerialPort.h \
        model/SocketThread.h \
        model/TcpSocket.h \
        view/ClientForm.h \
        view/ControlForm.h \
        view/DataForm.h \
        view/DataWidget.h \
        view/DockWidget.h \
        view/MainForm.h \
        view/ScrollArea.h \
        view/Widget.h \
        window.h
    
unix {
    target.path = /usr/lib
    INSTALLS += target
}
FORMS += \
    view/ClientForm.ui \
    view/ControlForm.ui \
    view/DataForm.ui \
    view/DataWidget.ui \
    view/MainForm.ui \
    view/ScrollArea.ui

RESOURCES += \
    Res.qrc

