#include "SerialPort.h"

#include <QDebug>

SerialPort::SerialPort(const QString &com) : m_strCom(com)
{
    init();
}

void SerialPort::init()
{
    m_serialPort = new QSerialPort();
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setPortName(m_strCom);
    connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(slot_readData()));
}

bool SerialPort::open()
{
    if(m_serialPort->isOpen())
    {
        m_serialPort->close();
    }

    if(!m_serialPort->open(QSerialPort::ReadWrite))
    {
        qDebug()<<"open serialPort "<<m_strCom<<" failed";
        return false;
    }
    return true;
}

void SerialPort::close()
{
    m_serialPort->close();
}

void SerialPort::sendCmd(const QByteArray &cmd)
{
    m_serialPort->write(cmd);
}

void SerialPort::slot_readData()
{
    QByteArray data = m_serialPort->readAll();
}
