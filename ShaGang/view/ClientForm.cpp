#include "ClientForm.h"
#include "ui_ClientForm.h"
#include <QDebug>

ClientForm::ClientForm(QString &strDev, QWidget *parent) : QWidget(parent),
    ui(new Ui::ClientForm), m_strDev(strDev)
{
    ui->setupUi(this);

    ui->widget->setInfo(strDev);

    m_isClicked = false;

    connect(ui->widget,SIGNAL(sig_clicked(QString&)),this,SLOT(slot_clicked(QString&)));
    connect(ui->widget,&Window::sig_doubleClicked,this,&ClientForm::slot_doubleClicked);

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

void ClientForm::executeCommand(const int cmd)
{
    qDebug()<<"ClientForm"<<__FUNCTION__<<cmd;
    ui->widget->executeCommand(cmd);
}

void ClientForm::slot_clicked(QString& info)
{
    emit sig_clicked(this, info);
}

void ClientForm::slot_doubleClicked(QString &info, bool value)
{
    emit sig_doubleClicked(this, info, value);
}

void ClientForm::slot_update()
{
    qDebug()<<"ClientForm"<<__FUNCTION__;
  //  ui->widget->executeCommand(1007);
}
