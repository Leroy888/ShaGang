#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QThread>

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket(const QString &ip, int port);
    ~TcpSocket();

    void sendCmd(const QByteArray &cmd);

    void disconnectFromHost();
    bool mapFile(const QString &fileName);

public slots:
    void slot_startConnect();
private:
    void initLogic();
private slots:
    void slot_readData();
    void slot_reconnect();
    void slot_connect();
    void slot_numTimeout();

    void slot_disconnect();
signals:
    void sig_startConnect(int);
private:
    QString m_ip;
    int m_port;
    QTimer *m_timer;
    QStringList m_dataList;

    QTimer *m_numTimer;
    int m_num;
    bool m_isInit;
    bool m_isTimeout;
    QMap<int,QByteArray> m_dataMap;
    QByteArray m_data;

    uchar* m_fileMap;
};

#endif // TCPSOCKET_H
