#ifndef LRSXXFILETHREAD_H
#define LRSXXFILETHREAD_H

#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QMap>

class LRSxxFileThread : public QThread
{
    Q_OBJECT
public:
    LRSxxFileThread(const QString &fileName, const QByteArray &data);

    void run();

private:
    QString m_fileName;
    QByteArray m_data;
    int m_num;
    void save();

    QMap<int,QByteArray> m_dataMap;
};

#endif // LRSXXFILETHREAD_H
