#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMap>
#include "com/Functions.h"

class JsonReader
{
public:
    JsonReader(const QString &fileName);

    void parseJson(QList<MenuData *> &menuDataList, QMap<QString, QList<MenuData *> > &childMenuDataMap, QMap<QString, QList<MenuData *> > &actionDataMap);

private:
    QString m_fileName;
};

#endif // JSONREADER_H
