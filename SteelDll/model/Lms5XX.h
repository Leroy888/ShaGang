#ifndef LMS5XX_H
#define LMS5XX_H

#include "DeviceModel.h"
#include "model/TcpSocket.h"

class Lms5XX : public DeviceModel
{
public:
    Lms5XX(const QString &ip, const int port);

    virtual void setParam(const QString &ip, int port) override;
    virtual void sendCmd(const QByteArray &cmd) override;
    virtual void start() override;
    virtual void stop() override;  
    virtual void connectToHost() override;
    virtual void disconnectFromHost() override;
    virtual void status() override;
    virtual void trig() override;
    virtual void autoTrig(bool value) override;

private:
    TcpSocket *m_socket;
};

#endif // LMS5XX_H
