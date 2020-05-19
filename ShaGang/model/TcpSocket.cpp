#include "TcpSocket.h"
#include "model/FileSaver.h"
#include <QDateTime>
#include <math.h>
#include "model/LRSxxFileThread.h"

#include <QDebug>

#define MaxNum 200

TcpSocket::TcpSocket(const QString &ip, int port) : m_ip(ip), m_port(port)
{
    initLogic();
    m_isInit = true;
    m_isTimeout = true;

 //   mapFile("");
}

TcpSocket::~TcpSocket()
{
    m_socket->disconnectFromHost();
    delete m_socket;
    delete m_timer;
}

bool TcpSocket::mapFile(const QString &fileName)
{
    QFile file(QString("./data.txt"));
    if(!file.open(QIODevice::Unbuffered | QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open"<<"failed";
        return false;
    }

    QByteArray data = file.readAll();
    file.close();

    uchar *pMap = file.map(0, data.size());
    if(pMap)
    {
        qDebug()<<"file map ok";
        return true;
    }
    else
    {
        qDebug()<<"file map failed";
        return false;
    }
}

bool TcpSocket::connectToHost()
{
    m_socket->connectToHost(m_ip, m_port);
    qDebug()<<__FUNCTION__<<m_ip<<m_port;
    m_timer->start(5000);
}

void TcpSocket::disconnectFromHost()
{
    m_socket->disconnectFromHost();
}

void TcpSocket::sendCmd(const QByteArray &cmd)
{
    m_socket->write(cmd);
}

void TcpSocket::initLogic()
{
    m_socket = new QTcpSocket;
    connect(m_socket,SIGNAL(connected()),this,SLOT(slot_connect()));
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(slot_readData()));
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(slot_reconnect()));

    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_reconnect()));

    m_num = 0;
    m_numTimer = new QTimer;
    connect(m_numTimer,&QTimer::timeout,this,&TcpSocket::slot_numTimeout);
}

void TcpSocket::slot_readData()
{
    QByteArray data = m_socket->readAll();

    if(QString(data).startsWith("\u0002sSN LMDscandata"))
    {
       // qDebug()<<"start data";
        m_data.clear();
    }

    m_data.append(data);
    if((QString(m_data).startsWith("\u0002sSN LMDscandata")) && (QString(m_data).endsWith("0\u0003")))
    {
        if(m_isInit)
        {
            m_isInit = false;
            m_numTimer->start(200);
        }
        if(m_isTimeout)
        {
            m_isTimeout = false;
            m_dataMap.insert(m_num % MaxNum, m_data);
            qDebug()<<"data "<<data;

            if((m_num % MaxNum) == 199)
            {
                qDebug()<<__FUNCTION__<<" data: "<<QString(data);

                FileSaver *saver = new FileSaver(QString("./data.txt"), m_dataMap, m_num % MaxNum);
                connect(saver,&FileSaver::finished,saver,&FileSaver::deleteLater);
                saver->start();
            }
        }
        m_dataList.append(QString(data));
    }
}

void TcpSocket::slot_reconnect()
{
    return;
    m_socket->abort();
    m_socket->connectToHost(m_ip, m_port);

    m_timer->start(10000);
    qDebug()<<"reconnect "<<m_ip<<m_port;
}

void TcpSocket::slot_connect()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
    qDebug()<<m_ip<<m_port<<"connected";
}

void TcpSocket::slot_numTimeout()
{
    m_num++;
    m_isTimeout = true;
}
