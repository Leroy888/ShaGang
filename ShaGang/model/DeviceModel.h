#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QString>
#include <QByteArray>
#include <QObject>
#include "com/Common.h"

#include <QDebug>

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    DeviceModel() {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void sendCmd(const QByteArray &cmd) = 0;
    virtual void disconnectFromHost() = 0;
    virtual void status() = 0;
    virtual void trig() = 0;
    virtual void autoTrig(bool value) = 0;

    virtual bool initSerial() = 0;

signals:
    void sig_data(QByteArray *);
    void sig_startConnect();
    void sig_sendCommand(const QByteArray&);
    void sig_reloadData();

    void sig_connectToPlc();
    void sig_updateXpos(int);

public slots:
    void slot_reloadData()
    {
        emit sig_reloadData();
        qDebug()<<"DeviceModel slot_reloadData";
    }

    void slot_updateData()
    {


    }
};


#endif // DEVICEMODEL_H
