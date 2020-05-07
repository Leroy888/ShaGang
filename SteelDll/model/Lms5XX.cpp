#include "Lms5XX.h"
#include "com/Command.h"

#include <QDebug>

Lms5XX::Lms5XX(const QString &ip, const int port, const QString &com)
{
    m_socket = new TcpSocket(ip, port);
    m_serial = new SerialPort(com);
}

void Lms5XX::setParam(const QString &ip, int port)
{

}

void Lms5XX::sendCmd(const QByteArray &cmd)
{
    qDebug()<<"send Comand "<<QString(cmd);
}

void Lms5XX::start()
{
    qDebug()<<"start scan "<<Command::start();

    m_serial->sendCmd(Command::start());

    //m_socket->sendCmd(Command::start());
}

void Lms5XX::stop()
{
    qDebug()<<"stop scan "<<Command::stopTrig();
    m_socket->sendCmd(Command::stopTrig());
}

void Lms5XX::connectToHost()
{
    m_socket->connectToHost();
    qDebug()<<__FUNCTION__;
}

void Lms5XX::disconnectFromHost()
{
    m_socket->disconnectFromHost();

}

void Lms5XX::status()
{
   // m_socket->sendCmd(Command::status());
    m_serial->sendCmd(Command::status());
    qDebug()<<__FUNCTION__<<Command::status();
}

void Lms5XX::trig()
{
    m_socket->sendCmd(Command::trig());
    qDebug()<<__FUNCTION__<<Command::trig();
}

void Lms5XX::autoTrig(bool value)
{
    if(value)
    {
        m_socket->sendCmd(Command::autoTrig());
        qDebug()<<__FUNCTION__<<"autoTrig"<<Command::autoTrig();
    }
    else
    {
        m_socket->sendCmd(Command::stopTrig());
        qDebug()<<__FUNCTION__<<"stopTrig"<<Command::stopTrig();
    }
}

bool Lms5XX::initSerial()
{
    qDebug()<<__FUNCTION__;
    if(m_serial)
    {
        return m_serial->initSerial();
    }
    else
    {
        qDebug()<<"m_serial is null";
    }
}
