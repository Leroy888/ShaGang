#include "ClientForm.h"
#include "ui_ClientForm.h"
#include <QDebug>

ClientForm::ClientForm(const QString &ip, int port, QString &strDev, QWidget *parent) :QWidget(parent), ui(new Ui::ClientForm),
  m_ip(ip), m_port(port)
{
    ui->setupUi(this);

    m_socket = new QTcpSocket();
    connect(ui->widget,SIGNAL(sig_clicked(QWidget*)),this,SLOT(slot_clicked()));

    m_devModel = DeviceFactory::getDevice(strDev);
}

ClientForm::~ClientForm()
{
    delete ui;
}

void ClientForm::mouseReleaseEvent(QMouseEvent *)
{
    emit sig_clicked(this);
}

void ClientForm::setInfo(const QString info)
{
    ui->widget->setInfo(info);
}

void ClientForm::setStyleSheet(const QString &styleSheet, bool value)
{
    ui->widget->setStyleColor(styleSheet, value);

}

void ClientForm::connectToHost()
{
     m_socket->connectToHost(m_ip, m_port);
     if(!m_socket->waitForConnected(3000))
     {
         qDebug()<<"connect to"<<m_ip<<"failed";
     }
     else
     {
         qDebug()<<"connect to"<<m_ip<<"successed";
     }
}

void ClientForm::start()
{
    m_devModel->start();
}

void ClientForm::stop()
{
    m_devModel->stop();
}

void ClientForm::sendCmd(const QByteArray &cmd)
{
    m_devModel->sendCmd(cmd);
}

void ClientForm::slot_clicked()
{
    emit sig_clicked(this);
    qDebug()<<"Client emit sig_clicked";
}
