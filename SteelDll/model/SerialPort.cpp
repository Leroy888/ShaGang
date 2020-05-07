#include "SerialPort.h"

#include <QDebug>

//SerialPort* SerialPort::m_instance = NULL;

SerialPort::SerialPort(const QString &port)
{
    m_serial = new QSerialPort;
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setPortName(port);
}

//SerialPort *SerialPort::getInstance()
//{
//    if(!m_instance)
//    {
//        m_instance = new SerialPort();
//    }

//    return m_instance;
//}

bool SerialPort::initSerial()
{
    if(m_serial)
    {
        qDebug()<<"SerialPort::initSerial()";
        return m_serial->open(QSerialPort::ReadWrite);
    }
    else
    {
        qDebug()<<"SerialPort serial is null";
        return false;
    }
}

void SerialPort::sendCmd(const QByteArray &cmd)
{
    m_serial->write(cmd);
}
