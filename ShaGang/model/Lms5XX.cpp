#include "Lms5XX.h"
#include "com/Command.h"

#include <QDebug>

Lms5XX::Lms5XX(const QString &ip, const int port, const QString &plcIp, const QString &device)
{
    m_socket = new TcpSocket(ip, port, device);

    connect(this,&Lms5XX::sig_startConnect,m_socket,&TcpSocket::slot_startConnect);
    connect(this,&Lms5XX::sig_sendCommand,m_socket,&TcpSocket::slot_sendCommand);
    connect(m_socket,&TcpSocket::sig_reloadData,this,&Lms5XX::slot_reloadData);
    connect(m_socket,&TcpSocket::sig_updateData,this,&Lms5XX::slot_updateData);

    m_timer = new QTimer;
    // m_timer->setInterval(3000);
    connect(m_timer,&QTimer::timeout,m_socket,&TcpSocket::slot_startConnect);
    connect(m_socket,SIGNAL(sig_startConnect(int)),m_timer,SLOT(start(int)));
    connect(m_socket,&TcpSocket::connected,m_timer,&QTimer::stop);
    connect(m_socket,SIGNAL(disconnected()),m_timer,SLOT(start()));

    m_numTimer = new QTimer;
    connect(m_socket,SIGNAL(sig_startTimer(int)),m_numTimer,SLOT(start(int)));
    connect(m_numTimer,&QTimer::timeout,m_socket,&TcpSocket::slot_numTimeout);

    m_thread = new QThread(this);
    m_socket->moveToThread(m_thread);
    m_timer->moveToThread(m_thread);
    m_numTimer->moveToThread(m_thread);
    m_thread->start();


    // PLC网络通信
    m_plcInstan = new PlcThread(plcIp);
    connect(this,&Lms5XX::sig_connectToPlc,m_plcInstan,&PlcThread::slot_connect);
    connect(m_plcInstan,&PlcThread::sig_updateXpos,m_socket,&TcpSocket::slot_updateXpos);

    m_plcTimer = new QTimer;
    connect(m_plcTimer,&QTimer::timeout,m_plcInstan,&PlcThread::slot_connect);

    m_plcThread = new QThread(this);
    m_plcTimer->moveToThread(m_plcThread);
    m_plcInstan->moveToThread(m_plcThread);
    m_plcThread->start();

    emit sig_startConnect();
    emit sig_connectToPlc();
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
}

void Lms5XX::sendCmd(const QByteArray &cmd)
{
    qDebug()<<"send Comand "<<QString(cmd);
}

void Lms5XX::start()
{
    qDebug()<<"start scan "<<Command::start();

    emit sig_sendCommand(Command::start());
}

void Lms5XX::stop()
{
    qDebug()<<"stop scan "<<Command::stopTrig();
    emit sig_sendCommand(Command::stopTrig());
}

void Lms5XX::disconnectFromHost()
{
   // m_socket->disconnectFromHost();
}

void Lms5XX::status()
{
    emit sig_sendCommand(Command::status());

    qDebug()<<__FUNCTION__<<Command::status();
}

void Lms5XX::trig()
{
    emit sig_sendCommand(Command::trig());
    qDebug()<<__FUNCTION__<<Command::trig();
}

void Lms5XX::autoTrig(bool value)
{
    if(value)
    {
        QByteArray cmd = QString("<STX>sEN LMDscandata 1<ETX>").toLatin1();
        QString("<STX>sRN LMDscandata<ETX>");

        emit sig_sendCommand(Command::autoTrig());
        qDebug()<<__FUNCTION__<<cmd;
    }
    else
    {
        emit sig_sendCommand(Command::stopTrig());
        qDebug()<<__FUNCTION__<<"stopTrig"<<Command::stopTrig();
    }
}

bool Lms5XX::initSerial()
{

}
