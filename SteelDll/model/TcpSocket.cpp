#include "TcpSocket.h"
#include "model/FileSaver.h"
#include <QDateTime>
#include <math.h>

#include <QDebug>

#define MaxNum 200

TcpSocket::TcpSocket(const QString &ip, int port) : m_ip(ip), m_port(port)
{
    initLogic();
    m_isInit = true;
    m_isTimeout = true;
}

TcpSocket::~TcpSocket()
{
    delete m_socket;
    delete m_timer;
}

bool TcpSocket::connectToHost()
{
    m_socket->connectToHost(m_ip, m_port);

    m_timer->start(3000);
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

    if(QString(data).split(" ").length() > 25)
    {
        if(m_isInit)
        {
            m_isInit = false;
            m_numTimer->start(200);
        }
        if(m_isTimeout)
        {
            m_isTimeout = false;
            m_dataMap.insert(m_num % MaxNum, data);
           // qDebug()<<"line "<<m_num<<" "<<QString()
        }

        m_dataList.append(QString(data));
    }
    else
    {
        if(!m_isInit)
        {
            FileSaver *saver = new FileSaver(QString("./data.txt"), m_dataMap, m_num % MaxNum);
            connect(saver,&FileSaver::finished,saver,&FileSaver::deleteLater);
            saver->start();
            qDebug()<<__FUNCTION__<<" data: "<<QString(data);
        }
    }
}

void TcpSocket::slot_reconnect()
{
    m_socket->abort();
    m_socket->connectToHost(m_ip, m_port);

    m_timer->start(3000);
}

void TcpSocket::slot_connect()
{
    if(m_timer->isActive())
    {
        m_timer->stop();
    }
}

void TcpSocket::slot_numTimeout()
{
    m_num++;
    m_isTimeout = true;
}
