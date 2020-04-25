#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include "model/TcpSocket.h"
#include <QTcpSocket>
#include <QMouseEvent>
#include "model/DeviceFactory.h"
#include "model/DeviceModel.h"


namespace Ui {
class ClientForm;
}

class ClientForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientForm(const QString &ip, int port, QString &strDev, QWidget *parent = nullptr);
    ~ClientForm();

    void mouseReleaseEvent(QMouseEvent*);

    void setInfo(const QString info);
    void setStyleSheet(const QString &styleSheet, bool value);

    void connectToHost();

    void start();
    void stop();
    void sendCmd(const QByteArray &cmd);

signals:
    void sig_clicked(QWidget*);

private slots:
    void slot_clicked();
private:
    Ui::ClientForm *ui;

    //TcpSocket *m_socket;
    QString m_ip;
    int m_port;
    QTcpSocket *m_socket;

    DeviceModel *m_devModel;
};

#endif // CLIENTFORM_H
