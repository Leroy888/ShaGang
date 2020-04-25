#include "TestPlugin.h"

#include <QDebug>

TestPlugin::TestPlugin()
{

}

void TestPlugin::setData(const QString &data)
{
    m_data  = data + "_测试插件";
}

QString TestPlugin::getStrData() const
{
    return m_data;
}

void TestPlugin::sendCmd(const QByteArray &cmd1, const QByteArray &cmd2)
{
    qDebug()<<__FUNCTION__<<" "<<cmd1<<" "<<cmd2;
}

Data TestPlugin::getData() const
{
    Data data;

    return data;
}
