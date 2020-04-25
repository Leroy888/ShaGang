#include "Functions.h"
#include <QDir>
#include <QDateTime>
#include <QApplication>
#include <QPluginLoader>

#include <QDebug>


Functions::Functions()
{

}

//bool Functions::loadPlugin(const QString &fileName, FuncInterface *interface)
//{
//    QDir dir(fileName);
//    QPluginLoader loader(fileName);
//    QObject *plugin = loader.instance();
//    if(plugin)
//    {
//        interface = qobject_cast<FuncInterface*> (plugin);
//        if(interface)
//        {
//            return true;
//        }
//    }
//    return false;
//}

void Functions::sleepMs(int ms)
{
    QDateTime dieTime = QDateTime::currentDateTime().addMSecs(ms);
    while(QDateTime::currentDateTime() < dieTime)
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

bool Functions::loadPlugin(const QString &fileName, UiInterface *interface)
{
    QDir dir(fileName);
    QPluginLoader loader(fileName);
    QObject *plugin = loader.instance();
    if(plugin)
    {
        interface = qobject_cast<UiInterface*> (plugin);
        if(interface)
        {
            return true;
        }
    }
    return false;
}

void Functions::mkDir(QString strPath)
{
   QStringList pathList = strPath.split("/");
   QString path = "";
   for(int i=0;i<pathList.length(); i++)
   {
       path = path + pathList.at(i);
       if(!QDir(path).exists())
       {
           if(!QDir().mkdir(path))
           {
               return;
           }
       }
       path = path + "/";
   }
}

QString Functions::stringListToString(const QStringList &list)
{
    QString str;
    for(int i=0; i<list.length(); i++)
    {
        if(i != list.length() - 1)
        {
            str = str + list.at(i) + ",";
        }
        else
        {
            str += list.at(i);
        }
    }

    return str;
}

void Functions::saveImage(const QImage &img, const QString &savePath, const QString &imgName, const QString &pcInfo, const QString &strRes)
{
    QDateTime curTime = QDateTime::currentDateTime();
    QString strDate = curTime.toString("yyyy-MM-dd");
    int hour = QTime::currentTime().hour();
    QString dute = QStringLiteral("/白班");
    if(hour < 8 || hour > 19)
    {
        dute = QStringLiteral("/晚班");
    }
    if(hour < 8)
    {
        strDate = curTime.addDays(-1).toString("yyyy-MM-dd");
    }

    QString path = savePath + "/" + strDate + "/" +pcInfo + dute + "/" + strRes ;

    Functions::mkDir(path);
    img.save((path + imgName));
}

