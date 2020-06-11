#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "DeviceModel.h"
#include "Lms5XX.h"
#include "LRS36xx.h"
#include <QString>

#include <QDebug>

class DeviceFactory
{
public:
    DeviceFactory() {}
    static DeviceModel* getDevice(const QString &devType, const QString &device, const QString &ip, const int port, const QString& plcIp)
    {
        qDebug()<<"devType ="<<devType<<" device ="<<device;
        if(devType.toUpper() == QString("LMS511"))
        {
            return new Lms5XX(ip, port, plcIp, devType, device);
        }
        else if(devType.toUpper() == QString("LRS3601"))
        {
            return new LRS36xx(ip, port, plcIp, devType, device);
        }
        else
        {
            return (DeviceModel*) nullptr;
        }
    }
};

#endif // DEVICEFACTORY_H
