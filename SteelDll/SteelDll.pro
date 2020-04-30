TEMPLATE = lib

CONFIG += plugin

TARGET = $$qtLibraryTarget(Steel)

QT += widgets network

INCLUDEPATH += ../MainApp \
                /include


DESTDIR += ../App/Plugins

LIBS += $$PWD/GLWidget.dll

FORMS += \
    Form.ui \
    SteelForm.ui \
    view/ClientForm.ui \
    view/ControlForm.ui

HEADERS += \
    Form.h \
    SteelForm.h \
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

SOURCES += \
    Form.cpp \
    SteelForm.cpp \
    clsSettings.cpp \
    com/Command.cpp \
    model/FileSaver.cpp \
    model/Lms5XX.cpp \
    model/SocketThread.cpp \
    model/TcpSocket.cpp \
    view/ClientForm.cpp \
    view/ControlForm.cpp \
    window.cpp
