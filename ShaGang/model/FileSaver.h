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
    FileSaver(const QString &fileName, const QMap<float,QByteArray> &dataMap, const int num);
  //  FileSaver(const QString &fileName, const QList<QByteArray> &dataList, const QMap<int, QPoint> pointMap);

    void run();

protected:
    void save();
    void saveFile();
    void mapFile();

signals:
    void sig_saveOver();
private:
    QString m_fileName;
    QByteArray m_data;
    int m_num;

    QMap<float,QByteArray> m_dataMap;
    uchar* m_fileMap;

    QList<QByteArray> m_dataList;
   // QMap<int,QPoint> m_pointMap;
    void saveMap();
};

#endif // FILESAVER_H
