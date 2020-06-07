#include "PlcThread.h"

PlcThread::PlcThread(const QString &ip, const int port) : m_ip(ip), m_port(port)
{
    m_isInit = true;
    m_isStop = false;
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&PlcThread::slot_connect);

    if(m_isInit)
    {
        m_isInit = false;
        m_client = new TS7Client;
    }

    m_timer->start(3000);
}

void PlcThread::run()
{
    while(!m_isStop)
    {
        byte bt[4] = {0x12,0x34,0x56,0x78};
        m_client->ReadArea((int)vArea, 0, 0, 8*4, 0x68, bt);


        emit sig_updateXpos(m_pos);

        msleep(10);
    }
}

void PlcThread::slot_stop(bool value)
{
    m_isStop = value;
}

void PlcThread::slot_connect()
{
    if(!m_client->Connected())
    {
        //重连
        const char* ip = m_ip.toStdString().data();
        m_client->ConnectTo(ip, 0, 1);
    }
}

void PlcThread::slot_startRead()
{
    run();
}
