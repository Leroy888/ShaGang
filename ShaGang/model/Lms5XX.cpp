#include "Lms5XX.h"

#include <QDebug>

Lms5XX::Lms5XX()
{

}

void Lms5XX::setParam(const QString &ip, int port)
{

}

void Lms5XX::sendCmd(const QByteArray &cmd)
{
    qDebug()<<"send Comand "<<QString(cmd);
}

bool Lms5XX::open()
{

    return true;
}

void Lms5XX::start()
{
    qDebug()<<"start scan";
}

void Lms5XX::stop()
{
    qDebug()<<"stop scan";
}

void Lms5XX::close()
{

}
