#include "JsonReader.h"
#include <QFile>

#include <QDebug>

JsonReader::JsonReader(const QString &fileName) : m_fileName(fileName)
{

}

void JsonReader::parseJson(QList<MenuData*>& menuDataList, QMap<QString,QList<MenuData*>>& childMenuDataMap,
                           QMap<QString,QList<MenuData*>>& actionDataMap)
{
    QFile file(m_fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"read json file failed";
        return;
    }
    QByteArray data = file.readAll();
    qDebug()<<"json data "<<QString(data);
    //QString strData = QString(data);
    file.close();

    QJsonParseError parseError;
    QJsonDocument jDoc(QJsonDocument::fromJson(data, &parseError));

    if(!(parseError.error == QJsonParseError::NoError))
    {
        qDebug()<<"parse json error:"<<parseError.errorString();
        return;
    }

    QJsonObject jObj = jDoc.object();
    QStringList keys = jObj.keys();
    qDebug()<<"root keys:"<<keys;
    if(keys.contains("button"))
    {
        QJsonArray array = jObj.value("button").toArray();
        for(int i=0; i<array.count(); i++)
        {
            QJsonValue value = array.at(i);
            if(value.isObject())
            {
                QJsonObject vObj = value.toObject();
                QStringList menuKeys = vObj.keys();
                QString menuText;
                foreach (QString mKey, menuKeys)
                {
                    if(vObj.value(mKey).isString())
                    {
                        //menu = ui->menuBar->addMenu(vObj.value(mKey).toString());
                        menuText = vObj.value(mKey).toString();
                        qDebug()<<"menuText "<<menuText;
                    }
                    else if(vObj.value(mKey).isArray())
                    {
                        QJsonArray actionArray = vObj.value(mKey).toArray();
                        QStringList actionList;
                        for(int j=0; j<actionArray.count(); j++)
                        {
                            if(actionArray.at(j).isObject())
                            {
                                QJsonObject actionObj = actionArray.at(j).toObject();
                                QString text = actionObj.value("name").toString();
                                actionList.append(text);

                                QString strDll = actionObj.value("dll").toString();
                                //menuMap.insert(text, strDll);
                            }
                        }
                       // actionMap.insert(menuText, actionList);
                    }
                }
            }
        }
    }
}
