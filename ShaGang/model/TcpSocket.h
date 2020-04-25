#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class TcpSocket : public QObject
{
    Q_OBJECT
public:
    TcpSocket(const QString &ip, int port);
    ~TcpSocket();

    bool connectToHost();
    void sendCmd(const QByteArray &cmd);

private:
    void initLogic();
private slots:
    void slot_readData();
    void slot_reconnect();
private:
    QString m_ip;
    int m_port;
    QTcpSocket *m_socket;
    QTimer *m_timer;
};

#endif // TCPSOCKET_H
