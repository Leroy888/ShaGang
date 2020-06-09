#include "PlcThread.h"
#include <math.h>

#include <QDebug>

PlcThread::PlcThread(const QString &ip) : m_ip(ip)
{
    m_isInit = true;
    m_isStop = false;
    m_pos = 0;
    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&PlcThread::slot_connect);

    if(m_isInit)
    {
        m_client = new TS7Client;
    }

    m_timer->start(3000);
}

void PlcThread::run()
{
    while(!m_isStop)
    {
        byte bt[4] = {0};

        m_client->DBRead(1, 0, 32, bt);

        int xPos = 0;
        for(int i=0; i<4; i++)
        {
            int num  = bt[i];
            double pw = pow(16, 2*(4 - i - 1));
            double sum = num * pw;
            xPos += sum;
        }
       // qDebug()<<"x pos ="<<xPos;
        if(m_pos != xPos)
        {
            emit sig_updateXpos(xPos);
        }

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
        qDebug()<<"connect to PLC"<<ip;
    }
    else
    {
        if(m_isInit)
        {
            m_isInit = false;
            run();
        }
    }
}

void PlcThread::slot_startRead()
{
    run();
}
