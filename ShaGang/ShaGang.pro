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
LIBS += $$PWD/libs/snap7.dll

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
    com/Common.cpp \
    model/FileSaver.cpp \
    model/JsonReader.cpp \
    model/LRS36xx.cpp \
    model/LRSxxFileThread.cpp \
    model/Lms5XX.cpp \
    model/PlcThread.cpp \
    model/SerialPort.cpp \
    model/SocketThread.cpp \
    model/TcpSocket.cpp \
    snap/snap7.cpp \
    view/ClientForm.cpp \
    view/ControlFrame.cpp \
    view/DataFrame.cpp \
    view/DataWidget.cpp \
    view/DockWidget.cpp \
    view/Form.cpp \
    view/Frame.cpp \
    view/MainForm.cpp \
    view/ScrollArea.cpp \
    view/Widget.cpp \
    window.cpp

HEADERS +=\
        ShaGangInterface.h \
        ShaGang_global.h \
        clsSettings.h \
        com/Command.h \
        com/Common.h \
        com/Global.h \
        model/CRingBuffer.h \
        model/DeviceFactory.h \
        model/DeviceModel.h \
        model/FileSaver.h \
        model/JsonReader.h \
        model/LRS36xx.h \
        model/LRSxxFileThread.h \
        model/Lms5XX.h \
        model/PlcThread.h \
        model/SerialPort.h \
        model/SocketThread.h \
        model/TcpSocket.h \
        snap/snap7.h \
        view/ClientForm.h \
        view/ControlFrame.h \
        view/DataFrame.h \
        view/DataWidget.h \
        view/DockWidget.h \
        view/Form.h \
        view/Frame.h \
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
    view/ControlFrame.ui \
    view/DataFrame.ui \
    view/DataWidget.ui \
    view/Form.ui \
    view/Frame.ui \
    view/MainForm.ui \
    view/ScrollArea.ui

RESOURCES += \
    Res.qrc

