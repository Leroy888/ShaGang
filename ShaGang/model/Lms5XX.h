#ifndef LMS5XX_H
#define LMS5XX_H

#include "DeviceModel.h"
#include "model/TcpSocket.h"
#include "model/SerialPort.h"
#include "model/PlcThread.h"
#include <QThread>
#include <QObject>
#include <QTimer>

class Lms5XX : public DeviceModel
{
    Q_OBJECT
public:
    Lms5XX(const QString &ip, const int port, const QString &plcIp, const QString &devType, const QString& device);

    virtual void sendCmd(const QByteArray &cmd) override;
    virtual void start() override;
    virtual void stop() override;  
    virtual void disconnectFromHost() override;
    virtual void status() override;
    virtual void trig() override;
    virtual void autoTrig(bool value) override;

    virtual bool initSerial() override;

private:
    TcpSocket *m_socket;

    QTimer* m_timer;
    QThread* m_thread;
    QTimer* m_numTimer;

    //PLC通信
    PlcThread* m_plcInstan;
    QTimer* m_plcTimer;
    QThread* m_plcThread;
};

#endif // LMS5XX_H
