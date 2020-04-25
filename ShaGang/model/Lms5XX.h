#ifndef LMS5XX_H
#define LMS5XX_H

#include "DeviceModel.h"

class Lms5XX : public DeviceModel
{
public:
    Lms5XX();

    virtual void setParam(const QString &ip, int port) override;
    virtual void sendCmd(const QByteArray &cmd) override;
    virtual bool open() override;
    virtual void start() override;
    virtual void stop() override;
    virtual void close() override;
};

#endif // LMS5XX_H
