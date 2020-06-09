#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "DeviceModel.h"
#include "Lms5XX.h"
#include "LRS36xx.h"
#include <QString>

class DeviceFactory
{
public:
    DeviceFactory() {}
    static DeviceModel* getDevice(const QString &device, const QString &ip, const int port, const QString& plcIp, const QString &com = "")
    {
        if(device.toUpper() == QString("LMS5XX"))
        {
            return new Lms5XX(ip, port, plcIp, device);
        }
        else if(device.toUpper() == QString("LRS3601"))
        {
            return new LRS36xx(ip, port, plcIp, device);
        }
        else
        {
            return (DeviceModel*) nullptr;
        }
    }
};

#endif // DEVICEFACTORY_H
