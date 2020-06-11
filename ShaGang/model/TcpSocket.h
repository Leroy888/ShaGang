#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QMap>
#include "com/Common.h"

const uint ptNum = 3950000;

class TcpSocket : public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket(const QString& ip, int port, const QString &devType, const QString& device);

    void connectHost(const QString& ip, int port);

    void slot_timeout();

public slots:
    void slot_connect();
    void slot_disconnect();
    void slot_readyRead();

    void slot_startConnect();
    void slot_sendCommand(const QByteArray& cmd);
    void slot_numTimeout();
    void slot_updateXpos(int pos);

    void slot_saveOver();

signals:
    void sig_startConnect(int);
    void sig_startTimer(int);
    void sig_reloadData();
    void sig_updateData();

private slots:

private:
    QString m_ip;
    int m_port;
    QString m_devType;
    QString m_device;
    QStringList m_dataList;
    QMap<float,QByteArray> m_dataMap;
    int m_num;
    bool m_isTimeout;
    QTimer* m_numTimer;
    bool m_isInit;
    bool m_bPlcCnnected;
    QByteArray m_data;


    int m_xPos; //PLC读取的X轴的位置
    int m_lastXpos; //上一次的位置
    int m_startXpos;
    int m_factors;
    ulong m_startAng;
    int m_angStep;
    ulong m_sum;
    QString m_curPos;
    QString m_lastPos;
    uint m_index;
    int m_xIndex;
    bool m_isStop;

    uint m_ptsNum;
    int m_readNum;

    void parseData(const QByteArray &data);
    void parseLms511(const QByteArray &data);
    void parse(const QByteArray &data, int start);
    void parseLrs3601(const QByteArray &data);
    void parseLRS3601Data(const QByteArray &data, int start);
};

#endif // TCPSOCKET_H
