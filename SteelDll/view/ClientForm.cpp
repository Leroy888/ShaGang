#include "ClientForm.h"
#include "ui_ClientForm.h"
#include <QDebug>

ClientForm::ClientForm(const QString &ip, int port, const QString &com, QString &strDev, QWidget *parent) : QWidget(parent),
    ui(new Ui::ClientForm), m_ip(ip), m_port(port), m_strCom(com), m_strDev(strDev)
{
    ui->setupUi(this);

    m_isClicked = false;

    m_socket = new TcpSocket(ip, port);
    connect(ui->widget,SIGNAL(sig_clicked(QString&)),this,SLOT(slot_clicked(QString&)));
    connect(ui->widget,&Window::sig_doubleClicked,this,&ClientForm::slot_doubleClicked);

    m_devModel = DeviceFactory::getDevice(strDev, ip, port, com);
}

ClientForm::~ClientForm()
{
    delete ui;
}

void ClientForm::mouseReleaseEvent(QMouseEvent *)
{
    QString info = ui->widget->getInfo();
    emit sig_clicked(this, info);
}

void ClientForm::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_isClicked = !m_isClicked;
    emit sig_doubleClicked(this, m_strDev, m_isClicked);
}

void ClientForm::setInfo(const QString info)
{
    ui->widget->setInfo(info);
}

QString ClientForm::getInfo() const
{
    return ui->widget->getInfo();
}

void ClientForm::setStyleSheet(const QString &styleSheet, bool value)
{
    ui->widget->setStyleColor(styleSheet, value);
}

void ClientForm::connectToHost()
{
    m_devModel->connectToHost();
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

void ClientForm::disconnectToHost()
{
    m_devModel->disconnectFromHost();
}

void ClientForm::status()
{
    m_devModel->status();
}

void ClientForm::trig()
{
    m_devModel->trig();
}

void ClientForm::autoTrig(bool value)
{
    m_devModel->autoTrig(value);
}

bool ClientForm::initSerial()
{
    qDebug()<<"ClientForm::initSerial()";
    return m_devModel->initSerial();
}

void ClientForm::slot_clicked(QString& info)
{
    emit sig_clicked(this, info);
    qDebug()<<"Client emit sig_clicked";
}

void ClientForm::slot_doubleClicked(QString &info, bool value)
{
    emit sig_doubleClicked(this, info, value);
}
