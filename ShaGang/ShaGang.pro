#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T09:21:50
#
#-------------------------------------------------

QT       += widgets serialport network

TARGET = ShaGang
TEMPLATE = lib
DESTDIR = ../App/plugins

INCLUDEPATH += ../MainApp

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
    glwidget.cpp \
    model/Lms5XX.cpp \
    model/SerialPort.cpp \
    model/TcpSocket.cpp \
    view/ClientForm.cpp \
    window.cpp

HEADERS +=\
        Form.h \
        ShaGangInterface.h \
        ShaGang_global.h \
        clsSettings.h \
        glwidget.h \
        model/DeviceFactory.h \
        model/DeviceModel.h \
        model/Lms5XX.h \
        model/SerialPort.h \
        model/TcpSocket.h \
        view/ClientForm.h \
        window.h
    
unix {
    target.path = /usr/lib
    INSTALLS += target
}
FORMS += \
    Form.ui \
    view/ClientForm.ui

RESOURCES += \
    Res.qrc

