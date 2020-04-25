#ifndef DEVICEFACTORY_H
#define DEVICEFACTORY_H

#include "DeviceModel.h"
#include "Lms5XX.h"
#include <QString>

class DeviceFactory
{
public:
    DeviceFactory() {}
    static DeviceModel* getDevice(const QString &device)
    {
        if(device.toUpper() == QString("LMS5XX"))
        {
            return new Lms5XX();
        }
        else
        {
            return (DeviceModel*) nullptr;
        }
    }
};

#endif // DEVICEFACTORY_H
