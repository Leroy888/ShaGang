#ifndef LMS5XX_H
#define LMS5XX_H

#include "DeviceModel.h"
#include "model/TcpSocket.h"
#include "model/SerialPort.h"

class Lms5XX : public DeviceModel
{
public:
    Lms5XX(const QString &ip, const int port, const QString &com);

    virtual void setParam(const QString &ip, int port) override;
    virtual void sendCmd(const QByteArray &cmd) override;
    virtual void start() override;
    virtual void stop() override;  
    virtual void connectToHost() override;
    virtual void disconnectFromHost() override;
    virtual void status() override;
    virtual void trig() override;
    virtual void autoTrig(bool value) override;

    virtual bool initSerial() override;
private:
    TcpSocket *m_socket;
    SerialPort *m_serial;
};

#endif // LMS5XX_H
