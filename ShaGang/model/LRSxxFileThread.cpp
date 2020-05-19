#include "LRSxxFileThread.h"
#include <QFile>
#include <QTextStream>
#include <QTextCodec>
#include <QMutex>
#include <QDateTime>
#include <math.h>

#include <QDebug>

LRSxxFileThread::LRSxxFileThread(const QString &fileName, const QByteArray &data) :
    m_fileName(fileName), m_data(data)
{
    m_num = 1;
}

void LRSxxFileThread::run()
{
    QMutex mutex;
    mutex.lock();
    QFile file(m_fileName);

    QStringList dataList = QString(m_data).split(" ");

    QTextStream os(&file);
    os.setRealNumberNotation(QTextStream::ScientificNotation);
    os.setRealNumberPrecision(17);
    // m_txt->setCodec(QTextCodec::codecForName("GB2312"));
    os.setCodec(QTextCodec::codecForName("UTF-8"));

    if(!file.open(QFile::Append))
    {
        qDebug()<<"Open "<<m_fileName<<"failed";
        return;
    }

    int i=2;
    bool ok;
    QString tmpNum;

    os<<QString("设备版本号: ")<<dataList.at(i++)<<endl;
    os<<QString("设备ID: ")<<dataList.at(i++)<<endl;
    os<<QString("设备序列号: ")<<dataList.at(i++)<<endl;
    os<<QString("设备状态: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
    os<<QString("指令计数: ")<<dataList.at(i++)<<endl;
    os<<QString("扫描计数: ")<<dataList.at(i++)<<endl;
    QString date = dataList.at(i++);
    qlonglong ss = date.toLongLong(&ok, 16);
    date = QDateTime::fromMSecsSinceEpoch(ss / 1000).toString("yyyy-MM-dd hh:mm:ss");
    os<<QString("扫秒起始时间: ")<<date<<endl;
    date = dataList.at(i++);
    ss  = date.toLongLong(&ok, 16);
    date = QDateTime::fromMSecsSinceEpoch(ss / 1000).toString("yyyy-MM-dd hh:mm:ss");
    os<<QString("扫描结束时间: ")<<date<<endl;
    os<<QString("开关量输入状态: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
    os<<QString("开关量输出状态: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
    QString strFreq = dataList.at(i++);
    int freq = strFreq.toUInt(&ok, 16) / 100;
    os<<QString("扫描频率: ")<<freq<<endl;
    os<<QString("编码器状态: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
    os<<QString("输出通道: ")<<dataList.at(i++)<<endl;
    os<<QString("回波层序号: ")<<dataList.at(i++)<<endl;
    os<<QString("起始角度: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
    os<<QString("角度分辨率: ")<<dataList.at(i++)<<endl;
    tmpNum = dataList.at(i++);
    os<<QString("测量数据个数: ")<<tmpNum.toInt(&ok, 16)<<endl;
    os<<QString("X轴: ")<<m_num<<endl;

    int factors = 1;
    if(dataList.at(21) == QString("40000000"))
    {
        factors = 2;
    }

    QString tmp = dataList.at(23);
    int startAng = tmp.toInt(&ok, 16) / 10000;
    qDebug()<<"start angle "<<startAng;

    tmp = dataList.at(24);
    int ang = tmp.toInt(&ok, 16);
    double angStep = ang / 10000.0;
    qDebug()<<"angle step "<<angStep;

    tmp = dataList.at(25);
    int dataNum = tmp.toInt(&ok, 16);

    double yMax = 0;
    double zMax = 0;
    for(int j=0; j< dataNum; j++)
    {
        tmp = dataList.at(26 + j);
        double z = tmp.toInt(&ok, 16) * factors * cos((startAng + j*angStep) / 180 * M_PI) / 1000;
        double y = tmp.toInt(&ok, 16) * factors * sin((startAng + j*angStep) / 180 * M_PI) / 1000;
        if(z > zMax)
            zMax = z;
        if(y > yMax)
            yMax = y;
        os<<m_num++<<" "<<y<<" "<<z<<" "<<1<<endl;
    }

    qDebug()<<"Max y "<<yMax;
    qDebug()<<"Max z "<<zMax;

    file.close();
    mutex.unlock();
}

void LRSxxFileThread::save()
{
    QFile file(m_fileName);
    QTextStream os(&file);
    os.setRealNumberNotation(QTextStream::ScientificNotation);
    os.setRealNumberPrecision(17);

    if(!file.open(QFile::ReadWrite))
    {
        qDebug()<<"Open "<<m_fileName<<"failed";
        return;
    }

    QList<int> keys = m_dataMap.keys();
    if(keys.length() == 0)
        return;
    QByteArray tmpData = m_dataMap.value(keys.at(0));
    QStringList dataList = QString(tmpData).split(" ");
    QString strTmp = dataList.at(2);
    os<<"MeshVersionFormatted "<<2<<endl;
    strTmp = dataList.at(3);
    os<<"Dimension"<<endl;
    os<<3<<endl;

    bool ok;
    strTmp = dataList.at(25);
    ulong sum = strTmp.toULong(&ok, 16);
    os<<"Vertices"<<endl;
    os<<sum*(keys.length())<<endl;

    int factors = 1;
    if(dataList.at(21) == QString("40000000"))
    {
        factors = 2;
    }

    strTmp = dataList.at(23);
    int startAng = strTmp.toInt(&ok, 16) / 10000;
    qDebug()<<"start angle "<<startAng;

    strTmp = dataList.at(24);
    int ang = strTmp.toInt(&ok, 16);
    double angStep = ang / 10000.0;
    qDebug()<<"angle step "<<angStep;


    for (int i=0; i<keys.length(); i++)
    {
        QByteArray data = m_dataMap.value(i);

        dataList.clear();
        dataList = QString(data).split(" ");

        double yMax = 0;
        double zMax = 0;
        for(int j=0; j< sum; j++)
        {
            strTmp = dataList.at(26 + j);
            double z = strTmp.toInt(&ok, 16) * factors * cos((startAng + j*angStep) / 180 * M_PI) / 1000;
            double y = strTmp.toInt(&ok, 16) * factors * sin((startAng + j*angStep) / 180 * M_PI) / 1000;
            if(z > zMax)
                zMax = z;
            if(y > yMax)
                yMax = y;
            os<<(double)i<<" "<<y<<" "<<z<<" "<<1<<endl;
        }
    }
    os<<"MeshStatus\n"<<0<<"\nEnd";

    file.close();
}
