#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMap>

class JsonReader
{
public:
    JsonReader(const QString &fileName);

    void parseJson(QMap<QString, QStringList> &menuMap, QMap<QString, QString> &plugMap);

private:
    QString m_fileName;
};

#endif // JSONREADER_H
