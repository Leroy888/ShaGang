#include "ShaGangPlugin.h"


#include <QDebug>

ShaGangPlugin::ShaGangPlugin()
{

}

QString ShaGangPlugin::getStrData() const
{
    return m_data;
}

void ShaGangPlugin::setData(const QString &data)
{
    m_data = data + "_沙钢插件";
}

void ShaGangPlugin::sendCmd(const QByteArray &cmd1, const QByteArray &cmd2)
{
    qDebug()<<__FUNCTION__<<cmd1<<" "<<cmd2;
}

Data ShaGangPlugin::getData() const
{
    Data data;
    data.area = 100;
    data.height = 101;
    data.length = 99;
    data.volume = 1000;
    data.weight = 2000;
    data.width = 98;

    return data;
}
