#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    SerialPort(const QString &port);
   // static SerialPort* getInstance();
    bool initSerial();
    void sendCmd(const QByteArray &cmd);

private:

    QString m_strCom;
   // static SerialPort* m_instance;
    QSerialPort *m_serial;
};

#endif // SERIALPORT_H
