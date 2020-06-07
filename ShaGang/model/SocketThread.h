#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QThread>
#include "TcpSocket.h"

class SocketThread : public QThread
{
    Q_OBJECT
public:
    SocketThread(const QString &ip, int port);

    void run();

private slots:
    void slot_readData();


private:
    QString m_ip;
    int m_port;

};

#endif // SOCKETTHREAD_H
