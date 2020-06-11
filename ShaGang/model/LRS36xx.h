#ifndef LRS36XX_H
#define LRS36XX_H

#include "DeviceModel.h"
#include "TcpSocket.h"
#include <QThread>
#include <QTimer>
#include "com/Common.h"
#include "model/PlcThread.h"
//#include "snap/snap7.h"

class LRS36xx : public DeviceModel
{
    Q_OBJECT
public:
    LRS36xx(const QString& ip, const int port, const QString& plcIp, const QString &devType, const QString &device);
    ~LRS36xx();

    virtual void start();
    virtual void stop();
    virtual void sendCmd(const QByteArray &cmd);
    virtual void disconnectFromHost();
    virtual void status();
    virtual void trig();
    virtual void autoTrig(bool value);

    virtual bool initSerial();

private:
    TcpSocket* m_socket;
    QTimer* m_timer;
    QThread* m_thread;

    QTimer* m_plcTimer;
    PlcThread *m_plcInstan;
    QThread* m_plcThread;

   // TS7Client* m_client;
};

#endif // LRS36XX_H
