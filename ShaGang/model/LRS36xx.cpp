#include "LRS36xx.h"
#include "com/Command.h"


LRS36xx::LRS36xx(const QString &ip, const int port, const QString &plcIp, const QString &devType, const QString& device)
{
    m_socket = new TcpSocket(ip, port, devType, device);
    connect(this,&LRS36xx::sig_startConnect,m_socket,&TcpSocket::slot_startConnect);
    connect(this,&LRS36xx::sig_sendCommand,m_socket,&TcpSocket::slot_sendCommand);

    m_timer = new QTimer;
    connect(m_socket,&TcpSocket::connected,m_timer,&QTimer::stop);
    connect(m_socket,SIGNAL(sig_startConnect(int)),m_timer,SLOT(start(int)));
    connect(m_timer,&QTimer::timeout,m_socket,&TcpSocket::slot_startConnect);
    connect(m_socket,SIGNAL(disconnected()),m_timer,SLOT(start()));

    m_thread = new QThread(this);
    m_socket->moveToThread(m_thread);
    m_timer->moveToThread(m_thread);
    m_thread->start();

    // PLC网络通信
    m_plcInstan = new PlcThread(device, plcIp);
    connect(this,&LRS36xx::sig_connectToPlc,m_plcInstan,&PlcThread::slot_connect);
    connect(m_plcInstan,&PlcThread::sig_updateXpos,m_socket,&TcpSocket::slot_updateXpos);

    m_plcTimer = new QTimer;
    connect(m_plcTimer,&QTimer::timeout,m_plcInstan,&PlcThread::slot_connect);

    m_plcThread = new QThread(this);
    m_plcTimer->moveToThread(m_plcThread);
    m_plcInstan->moveToThread(m_plcThread);
    m_plcThread->start();

    emit sig_startConnect();
    emit sig_connectToPlc();
}

LRS36xx::~LRS36xx()
{
    delete m_timer;
    delete m_plcTimer;
    delete m_socket;
    delete m_plcInstan;
    delete m_thread;
    delete m_plcThread;
}

void LRS36xx::start()
{
    qDebug()<<"start scan "<<Command::start();

    emit sig_sendCommand(Command::start());
}

void LRS36xx::stop()
{
    qDebug()<<"stop scan "<<Command::stopTrig();
    emit sig_sendCommand(Command::stopTrig());
}

void LRS36xx::sendCmd(const QByteArray &cmd)
{

}

void LRS36xx::disconnectFromHost()
{

}

void LRS36xx::status()
{
    emit sig_sendCommand(Command::status());
    qDebug()<<__FUNCTION__<<Command::status();
}

void LRS36xx::trig()
{
    emit sig_sendCommand(Command::trig());
    qDebug()<<__FUNCTION__<<Command::trig();
}

void LRS36xx::autoTrig(bool value)
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

bool LRS36xx::initSerial()
{

}
