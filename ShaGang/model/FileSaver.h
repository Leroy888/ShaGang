#ifndef FILESAVER_H
#define FILESAVER_H

#include <QObject>
#include <QThread>
#include <QString>
#include <QFile>

#include <QDebug>


class FileSaver :public QThread
{
    Q_OBJECT
public:
    FileSaver(const QString &fileName, const QByteArray &data, const int num);
    FileSaver(const QString &fileName, const QMap<int,QByteArray> &dataMap, const int num);

    void run();

protected:
    void save();
    void saveFile();
    void mapFile();
private:
    QString m_fileName;
    QByteArray m_data;
    int m_num;

    QMap<int,QByteArray> m_dataMap;
    uchar* m_fileMap;
};

#endif // FILESAVER_H
