#ifndef DEVICEMODEL_H
#define DEVICEMODEL_H

#include <QString>
#include <QByteArray>
#include <QObject>

class DeviceModel : public QObject
{
    Q_OBJECT
public:
    DeviceModel() {}
    virtual void setParam(const QString &ip, int port) = 0;
//    virtual void initDevice(const QString &strCom) = 0;
//    virtual void initDevice(const QString &ip, int port) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void sendCmd(const QByteArray &cmd) = 0;
    virtual bool open() = 0;
    virtual void close() = 0;

signals:
    void sig_data(QByteArray *);
};


#endif // DEVICEMODEL_H
