#include "SocketThread.h"

SocketThread::SocketThread(const QString &ip, int port) : m_ip(ip), m_port(port)
{
    m_socket = new TcpSocket(m_ip, m_port);
    m_socket->connectToHost();
}

void SocketThread::run()
{

    this->exec();
}

void SocketThread::slot_readData()
{

}
