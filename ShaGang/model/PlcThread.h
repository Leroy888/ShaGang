#ifndef PLCTHREAD_H
#define PLCTHREAD_H

#include <QObject>
#include <QThread>
#include "snap/snap7.h"
#include "com/Common.h"
#include <QTimer>

class PlcThread : public QThread
{
    Q_OBJECT
public:
    PlcThread(const QString& ip, const int port);

    void run();

signals:
    void sig_updateXpos(int);
    void sig_reconnect(int);

public slots:
    void slot_stop(bool value);
    void slot_connect();
    void slot_startRead();

private:
    bool m_isInit;
    QString m_ip;
    int m_port;
    bool m_isStop;
    int m_pos;

    TS7Client* m_client;
    QTimer* m_timer;
};

#endif // PLCTHREAD_H
