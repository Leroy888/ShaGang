#include "TcpSocket.h"
#include <QThread>
#include "FileSaver.h"
#include <math.h>
#include "com/Global.h"

#include <QDebug>

#define MaxNum  65535
#define LEN 1700
#define DIAMETER 85
#define FREQ 100000
#define STEP 0.085
const int dataLen = 395;

TcpSocket::TcpSocket(const QString &ip, int port, const QString &devType, const QString &device)
    : m_ip(ip), m_port(port), m_devType(devType), m_device(device)
{
    m_isInit = true;
    m_isTimeout = true;
    m_num = 0;
    m_lastPos = "";
    m_ptsNum = 0;
    m_readNum = 0;
    m_isStop = false;
    m_xIndex = -1;

    if(Global::m_ringBuffer)
    {
        qDebug()<<"Rinfbuffer init";
    }
    else
    {
        qDebug()<<"RingBuffer is nullptr";
    }

    connect(this,&TcpSocket::connected,this,&TcpSocket::slot_connect);
    connect(this,&TcpSocket::disconnected,this,&TcpSocket::slot_disconnect);
    connect(this,&TcpSocket::readyRead,this,&TcpSocket::slot_readyRead);

    m_numTimer = new QTimer;
    connect(m_numTimer,&QTimer::timeout,this,&TcpSocket::slot_numTimeout);

}

void TcpSocket::slot_timeout()
{
    this->abort();
    this->connectToHost(m_ip, m_port);
}

void TcpSocket::slot_sendCommand(const QByteArray &cmd)
{
    this->write(cmd);
}

void TcpSocket::connectHost(const QString &ip, int port)
{
    this->connectToHost(ip, port);
}

void TcpSocket::slot_connect()
{
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
}

void TcpSocket::slot_disconnect()
{
    emit sig_startConnect(3000);
    qDebug()<<__FUNCTION__<<QThread::currentThreadId();
}

void TcpSocket::slot_readyRead()
{
    QByteArray data = this->readAll();
//    if(!m_bPlcCnnected)
//    {
//        return;
//    }

    if(QString(data).contains(QString("\u0002sEA LMDscandata 1\u0003")))
    {
        return;
    }
    else if(QString(data) == QString("\x02sEN LMDscandata 0\x03"))
    {
        return;
    }

    if(m_devType == QString("LMS5XX"))
    {
        parseLms511(data);
    }
    else if(m_devType == QString("LRS3601"))
    {
        parseLrs3601(data);
    }
}

void TcpSocket::parseData(const QByteArray& data)
{
    if(m_devType == "LMS5XX")
    {
        parseLms511(data);
    }

}

void TcpSocket::parse(const QByteArray &data, int start)
{
    QStringList dataList = QString(data).split(" ");
    int endIndex = data.indexOf("0\x03", start);
    int endLen = QByteArray("0\x03").length();
    if(endIndex < 0)
    {
        return;
    }
    QByteArray tmpArry = data.mid(start, endIndex - start + endLen);
    int arrayLen = tmpArry.length();
    qDebug()<<"ArrayLen ="<<arrayLen;

    //  qDebug()<<"start"<<start<<"len"<<len<<"dataList"<<dataList;
    bool ok;
    if(m_isInit)
    {
        m_isInit = false;
        QString strTmp = dataList.at(start + 2);
        strTmp = dataList.at(start + 3 );

        strTmp = dataList.at(start + 27 );
        qDebug()<<"data sum "<<strTmp<<" #### test data sum "<<dataList.length();
        m_sum = strTmp.toULong(&ok, 16);

        strTmp = dataList.at(start + 19 );
       // m_startX = strTmp.toUInt(&ok, 16);
      //  m_startXpos = m_xPos;
        m_startXpos = GblRingBuffer::getInstance()->getXpos(m_device);
        m_lastXpos = m_xPos - 1; //第一次接收到数据，将 m_lastXpos值设置为 m_xPos - 1,为了使第一次数据也能写入缓冲区
        qDebug()<<"hex start x "<<strTmp<<" start x"<<m_startXpos;

        m_factors = 1;
        if(dataList.at(start + 23 ) == QString("40000000"))
        {
            m_factors = 2;
        }

        strTmp = dataList.at(start + 25);
        m_startAng = strTmp.toULong(&ok, 16);

        strTmp = dataList.at(start + 26 );
        m_angStep = strTmp.toInt(&ok, 16);
    }

    int btLen = data.length();

    while(!m_isStop)
    {
        if(start + btLen > arrayLen)
        {
            m_isStop = true;
            break;
        }
        else
        {
            QByteArray bytes = data.mid(start, btLen);
            QStringList dtList = QString(bytes).split(" ");
            if(dtList.endsWith(QString("0\u0003")))
            {
                m_xPos = GblRingBuffer::getInstance()->getXpos(m_device);
                if(m_lastXpos == m_xPos)
                {
                    return;
                }

                int xPos = (m_xPos - m_startXpos) % FREQ;   //计算从开始到当前 编码器转了多少分辨率

                qDebug()<<"xPos"<<xPos<<" m_xPos ="<<m_xPos<<" m_startXpos ="<<m_startXpos;

                double x = xPos * (M_PI * DIAMETER / FREQ); //得到当前x轴的实际坐标
                int xIndex = (x / STEP);    //得到x轴实际坐标对应的分辨率点
                qDebug()<<"xIndex"<<xIndex<<"m_xIndex"<<m_xIndex;

                if(xIndex == m_xIndex)
                {
                    return;
                }
                int nSize = (xIndex - m_xIndex) % PLOUGH_3D_SEGMENT_MAX;  //获取本次X轴对应的分辨率与上一个X轴对应的分辨率直接的差值
                qDebug()<<"xIndex ="<<xIndex<<" | m_xIndex ="<<m_xIndex;
                for(int k=m_xIndex+1; k<xIndex; k++)    //跳过的分辨率设置为disabled
                {
                    Global::m_ringBuffer->Enable(k, false);
                }
                Global::m_ringBuffer->Enable(xIndex, true);
                m_xIndex = xIndex;

                double zMax = 0;
                double yMax = 0;
                qDebug()<<"xIndex"<<xIndex<<" | m_index ="<<m_index<<" | m_sum"<<m_sum<<" | x"<<x<<" | nSize"<<nSize;

                for(int j=0; j< m_sum; j++)
                {
                    QString strTmp = dtList.at(start + 28 + j);
                    double z = strTmp.toInt(&ok, 16) * m_factors * cos((m_startAng + j*m_angStep) / (180 * 10000.0) * M_PI) ;
                    double y = strTmp.toInt(&ok, 16) * m_factors * sin((m_startAng + j*m_angStep) / (180 * 10000.0) * M_PI) ;

                    Global::m_ringBuffer->writePointData(xIndex, j, x, y, z);

                    m_ptsNum++;

                    if(z > zMax)
                        zMax = z;
                    if(y > yMax)
                        yMax = y;
                }
                qDebug()<<"x"<<x<<"yMax"<<yMax<<"zMax"<<zMax<<"len"<<m_ptsNum / m_sum;

                if(m_ptsNum % (400*m_sum) == 0)
                {
                    QString m_fileName = QString("D:/work/repos/mesh/crane.mesh");
                    QFile file(m_fileName);
                    QTextStream os(&file);
                    os.setRealNumberNotation(QTextStream::ScientificNotation);
                    os.setRealNumberPrecision(17);

                    if(!file.open(QFile::ReadWrite | QFile::Truncate))
                    {
                        qDebug()<<"Open "<<m_fileName<<"failed";
                        return;
                    }

                    os<<"MeshVersionFormatted "<<2<<endl;
                    os<<"Dimension\n"<<3<<endl;
                    os<<"Vertices"<<endl;
                    unsigned int count = Global::m_ringBuffer->getPointCount();
                    os<<count<<endl;

                    for (int var = 0; var < PLOUGH_3D_SEGMENT_MAX; ++var) {
                        Points3D* p3d = Global::m_ringBuffer->readSegmentData(var);
                        if(p3d->enabled)
                        {
                            for(int l = 0; l < PLOUGH_3D_SEGMENT_POINTS_MAX; l++)
                            {
                                os<<p3d->points[l].x<<" "<<p3d->points[l].y<<" "<<p3d->points[l].z<<" 1"<<endl;
                            }
                        }
                    }

                    os<<"MeshStatus\n"<<0<<"\nEnd";
                    qDebug()<<"save file end";

                    file.close();

                    emit sig_reloadData();
                    emit sig_updateData();
                }

                start += arrayLen;
            }
            else
            {
                QByteArray tmpHeader = QString("\u0002sSN").toLatin1();
                int tmp = data.indexOf(tmpHeader, start);
                qDebug()<<"tmp index "<<tmp;
                if(tmp + arrayLen > btLen)
                {
                    m_isStop = true;
                    start = tmp;
                    break;
                }
            }
        }
    }
    m_isStop = false;
    m_data.clear();
    if(data.length() > start)
    {
        m_data = data.right(data.length() - start);
    }
    qDebug()<<"start"<<start<<" end append m_data len"<<m_data.length()<<m_data;
}

void TcpSocket::parseLms511(const QByteArray &data)
{
    // 从这个开始 m_data
    //
    //读开头 biginIndex
    // 读结尾        endIndex
    // 完整包解析
    // m_data,data beginIndex

    // endindex
    // 完整包解析
    // 判断 最后一次 beginIndex 是m_data
    //  删除beginIndex之前的数据
    //m_data
    int tmpLen = data.length();
    qDebug()<<"*********************************************************************************************";
    qDebug()<<__FUNCTION__<<tmpLen<<data;
    int btLen = m_data.length();
    int headerIndex = data.indexOf("\x02sSN LMDscandata");
    int endIndex = -1;

    if(headerIndex >= 0)
    {
        endIndex = data.indexOf("0\x03", headerIndex);
    }


    qDebug()<<"header index"<<headerIndex;
    if(headerIndex == 0)
    {
        m_data.clear();
    }
    else if(headerIndex < 0)
    {
        if(m_data.isEmpty())
        {
            return;
        }
    }

    if(!m_data.isEmpty())
    {
        if(!m_data.startsWith("\x02sSN LMDscandata"))
        {
            qDebug()<<"header error"<<m_data.length()<<m_data;
            int index = m_data.indexOf("\x02sSN LMDscandata");
            if(index >= 0)
            {
                m_data = m_data.right(m_data.length() - index); //获取开头以后的数据，开头之前的数据丢弃
                qDebug()<<"index"<<index<<"m_data"<<m_data.length()<<m_data;
            }
            else
            {
                qDebug()<<"m_data has not \x02sSN LMDscandata clear m_data";
                m_data.clear();
            }
        }
        if(headerIndex > 0)
        {
            int len = (endIndex < headerIndex) ? endIndex : headerIndex;
            if(endIndex < 0)
            {
                m_data.append(data);
            }
            else
            {
                m_data.append(data.left(len));
            }

            qDebug()<<"end add m_data"<<m_data.length()<<m_data;
        }

        int companyLen = QString(m_data).split(" ").length();
        if(m_data.startsWith("\x02sSN LMDscandata") )
        {
            if(m_data.endsWith("0\x03") && companyLen == dataLen)
            {
                qDebug()<<"####################  start parse m_data ##################";

                parse(m_data, 0);
            }
            else
            {
                if(headerIndex < 0)
                {
                    m_data.append(data);
                    qDebug()<<"Append all data"<<data;
                }
                else
                {
                    m_data.append(data.left(headerIndex));
                    qDebug()<<"Append left"<<headerIndex<<"data"<<data;
                }

                qDebug()<<"Append m_data"<<m_data.length()<<m_data;
                if(m_data.endsWith("0\x03") && QString(m_data).split(" ").length() == dataLen)
                {
                    qDebug()<<"#################### after append start parse m_data ##################";
                    parse(m_data, 0);
                }
                else
                {
                    m_data.clear();
                }
            }
        }
        else
        {
            qDebug()<<"m_data header and end error"<<m_data.length()<<m_data;
        }
        // m_data.clear();
    }
    if(QString(data).split(" ").length() < dataLen)
    {
        m_data.append(data);
        qDebug()<<"empty m_data add "<<m_data.length()<<m_data;
    }
    else
    {
        qDebug()<<"####################  start parse data from"<<headerIndex<<" ##################";
        parse(data, headerIndex);
    }

    qDebug()<<"*********************************************************************************************\n";
}

void TcpSocket::parseLrs3601(const QByteArray& data)
{   
    qDebug()<<"*********************************************************************************************";
    int tmpLen = QString(data).split(" ").length();
    qDebug()<<"LRS3601 string data len ="<<tmpLen<<"data len ="<<data.length()<<data;
    int headerIndex = data.indexOf("\x02sSN LMDscandata");
    int endIndex = -1;

    if(headerIndex >= 0)
    {
        endIndex = data.indexOf("0\x03", headerIndex);
    }


    qDebug()<<"header index"<<headerIndex;
    if(headerIndex == 0)
    {
        m_data.clear();
    }
    else if(headerIndex < 0)
    {
        if(m_data.isEmpty())
        {
            return;
        }
    }

    if(!m_data.isEmpty())
    {
        if(!m_data.startsWith("\x02sSN LMDscandata"))
        {
            qDebug()<<"header error"<<m_data.length()<<m_data;
            int index = m_data.indexOf("\x02sSN LMDscandata");
            if(index >= 0)
            {
                m_data = m_data.right(m_data.length() - index); //获取开头以后的数据，开头之前的数据丢弃
                qDebug()<<"index"<<index<<"m_data"<<m_data.length()<<m_data;
            }
            else
            {
                qDebug()<<"m_data has not \x02sSN LMDscandata clear m_data";
                m_data.clear();
            }
        }
        if(headerIndex > 0)
        {
            int len = (endIndex < headerIndex) ? endIndex : headerIndex;
            if(endIndex < 0)
            {
                m_data.append(data);
            }
            else
            {
                m_data.append(data.left(len));
            }

            qDebug()<<"end add m_data"<<m_data.length()<<m_data;
        }

        int companyLen = QString(m_data).split(" ").length();
        if(m_data.startsWith("\x02sSN LMDscandata") )
        {
            if(m_data.endsWith("0\x03") && companyLen == dataLen)
            {
                qDebug()<<"####################  start parse m_data ##################";

                parseLRS3601Data(m_data, 0);
            }
            else
            {
                if(headerIndex < 0)
                {
                    m_data.append(data);
                    qDebug()<<"Append all data"<<data;
                }
                else
                {
                    m_data.append(data.left(headerIndex));
                    qDebug()<<"Append left"<<headerIndex<<"data"<<data;
                }

                qDebug()<<"Append m_data"<<m_data.length()<<m_data;
                if(m_data.endsWith("0\x03") && QString(m_data).split(" ").length() == dataLen)
                {
                    qDebug()<<"#################### after append start parse m_data ##################";
                    parseLRS3601Data(m_data, 0);
                }
                else
                {
                    m_data.clear();
                }
            }
        }
        else
        {
            qDebug()<<"m_data header and end error"<<m_data.length()<<m_data;
        }
        // m_data.clear();
    }
    if(QString(data).split(" ").length() < dataLen)
    {
        m_data.append(data);
        qDebug()<<"empty m_data add "<<m_data.length()<<m_data;
    }
    else
    {
        qDebug()<<"####################  start parse data from"<<headerIndex<<" ##################";
        parseLRS3601Data(data, headerIndex);
    }

    qDebug()<<"*********************************************************************************************\n";
}

void TcpSocket::parseLRS3601Data(const QByteArray &data, int start)
{
    QStringList dataList = QString(data).split(" ");
    int endIndex = data.indexOf("0\x03", start);
    int endLen = QByteArray("0\x03").length();
    if(endIndex < 0)
    {
        m_data.clear();
        m_data = data.right(data.length() - start);
        return;
    }
    QByteArray tmpArry = data.mid(start, endIndex - start + endLen);
    int arrayLen = tmpArry.length();
    qDebug()<<"ArrayLen ="<<arrayLen;

    //  qDebug()<<"start"<<start<<"len"<<len<<"dataList"<<dataList;
    bool ok;
    if(m_isInit)
    {
        m_isInit = false;
        QString strTmp = dataList.at(start + 2);
        strTmp = dataList.at(start + 3 );

        strTmp = dataList.at(start + 25 );
        qDebug()<<"data sum "<<strTmp<<" m_sum ="<<m_sum<<" #### test data sum "<<dataList.length();
        m_sum = strTmp.toULong(&ok, 16);

      //  m_startXpos = m_xPos;
        m_startXpos = GblRingBuffer::getInstance()->getXpos(m_device);
        m_lastXpos = m_xPos - 1; //第一次接收到数据，将 m_lastXpos值设置为 m_xPos - 1,为了使第一次数据也能写入缓冲区
        qDebug()<<" start x"<<m_startXpos;

        m_factors = 1;
        if(dataList.at(start + 21 ) == QString("40000000"))
        {
            m_factors = 2;
        }

        strTmp = dataList.at(start + 23);
        m_startAng = strTmp.toULong(&ok, 16);

        strTmp = dataList.at(start + 24 );
        m_angStep = strTmp.toInt(&ok, 16);
    }

    int btLen = data.length();

    while(!m_isStop)
    {
        if(start + btLen > arrayLen)
        {
            m_isStop = true;
            break;
        }
        else
        {
            QByteArray bytes = data.mid(start, btLen);
            QStringList dtList = QString(bytes).split(" ");
            if(dtList.endsWith(QString("0\u0003")))
            {
                m_xPos = GblRingBuffer::getInstance()->getXpos(m_device);
                if(m_lastXpos == m_xPos)
                {
                    return;
                }

                int xPos = (m_xPos - m_startXpos) % FREQ;   //计算从开始到当前 编码器转了多少分辨率

                qDebug()<<"xPos"<<xPos<<" m_xPos ="<<m_xPos<<" m_startXpos ="<<m_startXpos;

                double x = xPos * (M_PI * DIAMETER / FREQ); //得到当前x轴的实际坐标
                int xIndex = (x / STEP);    //得到x轴实际坐标对应的分辨率点
                qDebug()<<"xIndex"<<xIndex<<"m_xIndex"<<m_xIndex;

                if(xIndex == m_xIndex)
                {
                    return;
                }
                int nSize = (xIndex - m_xIndex) % PLOUGH_3D_SEGMENT_MAX;  //获取本次X轴对应的分辨率与上一个X轴对应的分辨率直接的差值
                qDebug()<<"xIndex ="<<xIndex<<" | m_xIndex ="<<m_xIndex;
                for(int k=m_xIndex+1; k<xIndex; k++)    //跳过的分辨率设置为disabled
                {
                   // Global::m_ringBuffer->Enable(k, false);
                    GblRingBuffer::getInstance()->getInstance()->getRingBuffer(m_device)->Enable(k, false);
                }
               // Global::m_ringBuffer->Enable(xIndex, true);
                GblRingBuffer::getInstance()->getRingBuffer(m_device)->Enable(xIndex, true);
                m_xIndex = xIndex;


                double zMax = 0;
                double yMax = 0;
                qDebug()<<"xIndex"<<xIndex<<" | m_index ="<<m_index<<" | m_sum"<<m_sum<<" | x"<<x<<" | nSize"<<nSize;

                for(int j=0; j< m_sum; j++)
                {
                    QString strTmp = dtList.at(start + 26 + j);
                    double z = strTmp.toInt(&ok, 16) * m_factors * cos((m_startAng + j*m_angStep) / (180 * 10000.0) * M_PI) ;
                    double y = strTmp.toInt(&ok, 16) * m_factors * sin((m_startAng + j*m_angStep) / (180 * 10000.0) * M_PI) ;

                   // Global::m_ringBuffer->writePointData(xIndex, j, x, y, z);
                    GblRingBuffer::getInstance()->getRingBuffer(m_device)->writePointData(xIndex, j, x, y, z);

                    m_ptsNum++;

                    if(z > zMax)
                        zMax = z;
                    if(y > yMax)
                        yMax = y;
                }
                qDebug()<<"x"<<x<<"yMax"<<yMax<<"zMax"<<zMax<<"len"<<m_ptsNum / m_sum;

                if(m_ptsNum % (10*m_sum) == 0)
                {
                    QString m_fileName = QString("D:/work/repos/mesh/crane.mesh");
                    QFile file(m_fileName);
                    QTextStream os(&file);
                    os.setRealNumberNotation(QTextStream::ScientificNotation);
                    os.setRealNumberPrecision(17);

                    if(!file.open(QFile::ReadWrite | QFile::Truncate))
                    {
                        qDebug()<<"Open "<<m_fileName<<"failed";
                        return;
                    }

                    os<<"MeshVersionFormatted "<<2<<endl;
                    os<<"Dimension\n"<<3<<endl;
                    os<<"Vertices"<<endl;
                  //  unsigned int count = Global::m_ringBuffer->getPointCount();
                    unsigned int count = GblRingBuffer::getInstance()->getRingBuffer(m_device)->getPointCount();
                    os<<count<<endl;

                    for (int var = 0; var < PLOUGH_3D_SEGMENT_MAX; ++var) {
                       // Points3D* p3d = Global::m_ringBuffer->readSegmentData(var);
                        Points3D* p3d = GblRingBuffer::getInstance()->getRingBuffer(m_device)->readSegmentData(var);
                        if(p3d->enabled)
                        {
                            for(int l = 0; l < PLOUGH_3D_SEGMENT_POINTS_MAX; l++)
                            {
                                os<<p3d->points[l].x<<" "<<p3d->points[l].y<<" "<<p3d->points[l].z<<" 1"<<endl;
                            }
                        }
                    }

                    os<<"MeshStatus\n"<<0<<"\nEnd";
                    qDebug()<<"save file end";

                    file.close();

                    emit sig_reloadData();
                    emit sig_updateData();
                }

                start += arrayLen;
            }
            else
            {
                QByteArray tmpHeader = QString("\u0002sSN").toLatin1();
                int tmp = data.indexOf(tmpHeader, start);
                qDebug()<<"tmp index "<<tmp;
                if(tmp + arrayLen > btLen)
                {
                    m_isStop = true;
                    start = tmp;
                    break;
                }
            }
        }
    }
    m_isStop = false;
    m_data.clear();
    if(data.length() > start)
    {
        m_data = data.right(data.length() - start);
    }
    qDebug()<<"start"<<start<<" end append m_data len"<<m_data.length()<<m_data;
}

void TcpSocket::slot_startConnect()
{
    this->abort();
    this->connectToHost(m_ip, m_port);

    emit sig_startConnect(3000);
    qDebug()<<__FUNCTION__<<m_ip<<m_port<<QThread::currentThreadId();
}

void TcpSocket::slot_numTimeout()
{
    m_isTimeout = true;
}

void TcpSocket::slot_updateXpos(int pos)
{
    m_xPos = pos;
    if(!m_bPlcCnnected)
    {
        m_bPlcCnnected = true;
    }
}

void TcpSocket::slot_saveOver()
{
    emit sig_reloadData();
    qDebug()<<"TcpSocket "<<__FUNCTION__;
}
