#include "FileSaver.h"
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <math.h>
#include <QTextCodec>

#include <QDebug>

FileSaver::FileSaver(const QString &fileName, const QByteArray &data, const int num)
    : m_fileName(fileName), m_data(data), m_num(num)
{

}

FileSaver::FileSaver(const QString &fileName, const QMap<int, QByteArray> &dataMap, const int num)
{
    m_fileName = fileName;
    m_dataMap = dataMap;

}

void FileSaver::run()
{

//    mapFile();


//    return;



    save();

    return;

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

    os<<QString("设备版本号: ")<<dataList.at(i++)<<endl;
    os<<QString("设备ID: ")<<dataList.at(i++)<<endl;
    os<<QString("设备序列号: ")<<dataList.at(i++)<<endl;
    os<<QString("设备状态: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
   // QString data = dataList.at(i++);
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
  //  os<<QString("编码器位置: ")<<dataList.at(i++)<<endl;  19
  //  os<<QString("编码器速度: ")<<dataList.at(i++)<<endl;  20
    os<<QString("输出通道: ")<<dataList.at(i++)<<endl;
    os<<QString("回波层序号: ")<<dataList.at(i++)<<endl;
    os<<QString("起始角度: ")<<dataList.at(i++)<<" "<<dataList.at(i++)<<" "<<dataList.at(i++)<<endl;
    os<<QString("角度分辨率: ")<<dataList.at(i++)<<endl;
    os<<QString("测量数据个数: ")<<dataList.at(i++)<<endl;
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

    QList<double> yList;
    QList<double> zList;

//    QStringList strYList;
//    QStringList strZList;
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
        os<<m_num<<" "<<y<<" "<<z<<" "<<1<<endl;
    }

    qDebug()<<"Max y "<<yMax;
    qDebug()<<"Max z "<<zMax;

    file.close();
    mutex.unlock();
}

void FileSaver::save()
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
    qDebug()<<"write header";
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
    qDebug()<<"get factors";
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

void FileSaver::saveFile()
{
    QFile objInputFile("./test.txt");
    if (!objInputFile.open(QIODevice::Unbuffered | QIODevice::ReadOnly))
    {
        return ;
    }

    QByteArray data = objInputFile.readAll();

    QFile objOutputFile("./test2.txt");
    if (!objOutputFile.open(QIODevice::Unbuffered | QIODevice::ReadWrite | QIODevice::Truncate))
    {
        objInputFile.close();
        return ;
    }

    uchar * pInputData;
    uchar * pOutputData;
    qint64 m_qint64FileOffset = 0;

    objOutputFile.resize(data.size());

    int unTmpBlockSize = data.size();

    pInputData = objInputFile.map(m_qint64FileOffset,unTmpBlockSize);

    std::string strData = data.toStdString();

    pOutputData = objOutputFile.map(m_qint64FileOffset,unTmpBlockSize);
    if (pOutputData == NULL)
    {
        objInputFile.close();
        objOutputFile.close();
        return ;
    }

    memcpy(pOutputData,strData.data(),data.size());
    objOutputFile.unmap(pOutputData);

    objOutputFile.close();

    return;
}

void FileSaver::mapFile()
{
    QFile file(m_fileName);
    if(!file.open(QIODevice::Unbuffered | QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug()<<"open"<<m_fileName<<"failed";
        return;
    }

    QList<int> keys = m_dataMap.keys();
    if(keys.length() == 0)
        return;
    file.resize(1024*1024*15);

    QByteArray tmpData = m_dataMap.value(keys.at(0));
    QStringList dataList = QString(tmpData).split(" ");
    QString strTmp = dataList.at(2);
    QString strFile;
    strFile = strFile + ("MeshVersionFormatted ") + (QString::number(2)) + ("\n");

    strFile = strFile + (QString("Dimension")) + ("\n") + (QString::number(3)) + "\n";

    bool ok;
    strTmp = dataList.at(25);
    int sum = strTmp.toUInt(&ok, 16);

    strFile = strFile + ("Vertices\n");
    strFile = strFile + (QString::number(sum*(keys.length()))) + ("\n");

    qDebug()<<"file size "<<file.size();
    uchar *pMap = file.map(0, file.size());
    int size = strFile.toLatin1().size();
    if(pMap)
    {
        memcpy(pMap, strFile.toStdString().data(), size);
    }
    else
    {
        qDebug()<<"file map failed";
        return;
    }

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

    qDebug()<<"X num "<<keys.length();
    for(int i=0; i<keys.length(); i++)
    {
        QByteArray dataxx = m_dataMap.value(i);
        char sp = ' ';
        QList<QByteArray> lArry = dataxx.split(sp);
        QStringList xxList = QString(dataxx).split(" ");
        QString xx = xxList.at(25);
        sum = xx.toUInt(&ok, 16);

        for(int j=0; j< sum; j++)
        {
            strTmp = xxList.at(26 + j);
            double z = strTmp.toInt(&ok, 16) * factors * cos((startAng + j*angStep) / 180 * M_PI) / 1000;
            double y = strTmp.toInt(&ok, 16) * factors * sin((startAng + j*angStep) / 180 * M_PI) / 1000;

            double x = (double)i;

            QString tmpStr = (QString::number(x, 'e', 17)) + (" ") + (QString::number(y, 'e', 17)) + (" ")
                             + (QString::number(z, 'e', 17)) + ("\n");

            int len = tmpStr.toLatin1().size();
            memcpy(pMap+size, tmpStr.toStdString().data(), len);
            size = size+len;
        }
    }

    strFile = ("MeshStatus\n0\nEnd");
    QByteArray data = strFile.toLatin1();
    file.resize(data.size());

    if(pMap)
    {
        //memcpy(pOutputData,strData.data(),data.size());
        memcpy(pMap + size, strFile.toStdString().data(), data.size());
        file.unmap(pMap);
        qDebug()<<"file unmap";
    }
    else
    {
        qDebug()<<"file map failed";
    }

    file.close();
}
