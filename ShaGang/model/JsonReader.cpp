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

    file.close();

    QJsonParseError parseError;
    QJsonDocument jDoc(QJsonDocument::fromJson(data, &parseError));

    if(!(parseError.error == QJsonParseError::NoError))
    {
        qDebug()<<"form parse json error:"<<parseError.errorString();
        return;
    }

    menuDataList.clear();
    childMenuDataMap.clear();
    actionDataMap.clear();

    QJsonObject jObj = jDoc.object();
    QStringList keys = jObj.keys();

    if(keys.contains("menus"))
    {
        QJsonArray array = jObj.value("menus").toArray();
        if(array.isEmpty())
        {
            return;
        }

        for(int i=0; i<array.count(); i++) //主菜单
        {
            QJsonValue value = array.at(i);
            if(value.isObject())
            {
                QJsonObject vObj = value.toObject();
                QString menuText = vObj.value("CN_menu").toString();
                QString enMenuText = vObj.value("EN_menu").toString();
                QString cmd = vObj.value("cmd").toString();
                int cmd_id = vObj.value("cmd_id").toInt();

                MenuData* pData = new MenuData;
                pData->CN_menu = menuText;
                pData->EN_menu = enMenuText;
                pData->cmd = cmd;
                pData->cmd_id = cmd_id;
                pData->enabled = vObj.value("enabled").toBool();
                pData->icon = vObj.value("icon").toString();

                QJsonArray childArr = vObj.value("child").toArray();
                if(!childArr.isEmpty())
                {
                    QList<MenuData*> childMenuDataList;
                    QList<MenuData*> actionDataList;
                    for(int j=0; j<childArr.count(); j++) //子菜单 或者action
                    {
                        QJsonValue chlValue = childArr.at(j);
                        if(chlValue.isObject())
                        {
                            QJsonObject chlObj = chlValue.toObject();
                            MenuData* ppData = new MenuData;
                            ppData->CN_menu = chlObj.value("CN_menu").toString();
                            ppData->EN_menu = chlObj.value("EN_menu").toString();
                            ppData->cmd = chlObj.value("cmd").toString();
                            ppData->cmd_id = chlObj.value("cmd_id").toInt();
                            ppData->enabled = chlObj.value("enabled").toBool();
                            ppData->shortcut = chlObj.value("shortcut").toString();
                            ppData->icon = chlObj.value("icon").toString();

                            QJsonArray chArray = chlObj.value("child").toArray();
                            if(chArray.isEmpty())
                            {
                                actionDataList.append(ppData);
                                actionDataMap.insert(pData->CN_menu, actionDataList);
                            }
                            else
                            {
                                childMenuDataList.append(ppData);
                                QList<MenuData*> childActionDataList;

                                foreach (QJsonValue jvalue, chArray) {
                                    QJsonObject actionObj = jvalue.toObject();
                                    MenuData *pppData = new MenuData;
                                    pppData->CN_menu = actionObj.value("CN_menu").toString();
                                    pppData->EN_menu = actionObj.value("EN_menu").toString();
                                    pppData->cmd = actionObj.value("cmd").toString();
                                    pppData->cmd_id = actionObj.value("cmd_id").toInt();
                                    pppData->enabled = actionObj.value("enabled").toBool();
                                    pppData->shortcut = actionObj.value("shortcut").toString();
                                    pppData->icon = actionObj.value("icon").toString();

                                    childActionDataList.append(pppData);
                                }
                                actionDataMap.insert(ppData->CN_menu, childActionDataList);
                            }
                        }
                    }
                    menuDataList.append(pData);
                    childMenuDataMap.insert(pData->CN_menu, childMenuDataList);
                }
            }
        }
    }
}
