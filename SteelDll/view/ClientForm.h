#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include "model/TcpSocket.h"
#include <QTcpSocket>
#include <QMouseEvent>
#include "model/DeviceFactory.h"
#include "model/DeviceModel.h"
#include "model/TcpSocket.h"
#include "model/SerialPort.h"


namespace Ui {
class ClientForm;
}

class ClientForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientForm(const QString &ip, int port, const QString &com, QString &strDev, QWidget *parent = nullptr);
    ~ClientForm();

    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void setInfo(const QString info);
    QString getInfo() const;
    void setStyleSheet(const QString &styleSheet, bool value);

    void connectToHost();

    void start();
    void stop();
    void sendCmd(const QByteArray &cmd);
     void disconnectToHost();
     void status();
     void trig();
     void autoTrig(bool value);

     bool initSerial();

signals:
    void sig_clicked(QWidget*, QString&);
    void sig_doubleClicked(QWidget*, QString&, bool);

private slots:
    void slot_clicked(QString &info);
    void slot_doubleClicked(QString &info, bool value);
private:
    Ui::ClientForm *ui;

    TcpSocket *m_socket;
    SerialPort *m_serial;
    QString m_strDev;
    QString m_ip;
    int m_port;
    QString m_strCom;

    DeviceModel *m_devModel;

    bool m_isClicked;
};

#endif // CLIENTFORM_H
