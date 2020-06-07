#include "ClientForm.h"
#include "ui_ClientForm.h"
#include <QDebug>

ClientForm::ClientForm(QString &strDev, QWidget *parent) : QWidget(parent),
    ui(new Ui::ClientForm), m_strDev(strDev)
{
    ui->setupUi(this);

    ui->frame->setInfo(strDev);

    m_isClicked = false;

    connect(ui->frame,SIGNAL(sig_clicked(QString&)),this,SLOT(slot_clicked(QString&)));
    connect(ui->frame,&Window::sig_doubleClicked,this,&ClientForm::slot_doubleClicked);

}

ClientForm::~ClientForm()
{
    delete ui;
}

void ClientForm::mouseReleaseEvent(QMouseEvent *)
{
    QString info = ui->frame->getInfo();
    emit sig_clicked(this, info);
}

void ClientForm::mouseDoubleClickEvent(QMouseEvent *event)
{
    m_isClicked = !m_isClicked;
    emit sig_doubleClicked(this, m_strDev, m_isClicked);
}

void ClientForm::setInfo(const QString info)
{
    ui->frame->setInfo(info);
}

QString ClientForm::getInfo() const
{
    return ui->frame->getInfo();
}

void ClientForm::setStyleSheet(const QString &styleSheet, bool value)
{
    ui->frame->setStyleColor(styleSheet, value);
}

void ClientForm::executeCommand(const int cmd)
{
    qDebug()<<"ClientForm"<<__FUNCTION__<<cmd;
    ui->frame->executeCommand(cmd);
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
    ui->frame->executeCommand(1007);
}
