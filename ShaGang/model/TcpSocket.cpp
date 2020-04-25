#include "TcpSocket.h"

TcpSocket::TcpSocket(const QString &ip, int port) : m_ip(ip), m_port(port)
{
    initLogic();
}

TcpSocket::~TcpSocket()
{
    delete m_socket;
    delete m_timer;
}

bool TcpSocket::connectToHost()
{
    m_socket->connectToHost(m_ip, m_port);
    if(!m_socket->waitForConnected(3000))
    {
        m_timer->start(3500);

    }
    else
    {
        m_timer->stop();
    }
}

void TcpSocket::sendCmd(const QByteArray &cmd)
{
    m_socket->write(cmd);
}

void TcpSocket::initLogic()
{
    m_socket = new QTcpSocket;
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(slot_readData()));
    connect(m_socket,SIGNAL(disconnected()),this,SLOT(slot_reconnect()));

    m_timer = new QTimer();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_reconnect()));
}

void TcpSocket::slot_readData()
{
    QByteArray data = m_socket->readAll();
}

void TcpSocket::slot_reconnect()
{
//    m_socket->connectToHost(m_ip, m_port);
//    if(!m_socket->waitForConnected(3000))
//    {
//        m_timer->start(3500);
//    }
//    else
//    {
//        m_timer->stop();
//    }
}
