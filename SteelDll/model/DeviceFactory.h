#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "DeviceModel.h"
#include "Lms5XX.h"
#include <QString>

class DeviceFactory
{
public:
    DeviceFactory() {}
    static DeviceModel* getDevice(const QString &device, const QString &ip, const int port)
    {
        if(device.toUpper() == QString("LMS5XX"))
        {
            return new Lms5XX(ip, port);
        }
        else
        {
            return (DeviceModel*) nullptr;
        }
    }
};

#endif // DEVICEFACTORY_H
