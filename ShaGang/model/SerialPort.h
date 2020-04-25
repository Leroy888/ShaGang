#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QWidget>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(const QString& com);

    bool open();
    void close();
    void sendCmd(const QByteArray &cmd);

private slots:
    void slot_readData();
private:
    void init();
private:
    QString m_strCom;
    QSerialPort *m_serialPort;
};

#endif // SERIALPORT_H
