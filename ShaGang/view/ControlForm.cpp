#include "ControlForm.h"
#include "ui_ControlForm.h"
#include "com/Command.h"
#include <QMatrix>
#include "../MainApp/com/Functions.h"

ControlForm::ControlForm(const QString &info, const QString &type, const QString &ip, Widget *parent) :
    Widget(parent), ui(new Ui::ControlForm),  m_info(info)
{
    ui->setupUi(this);
    ui->btnShow->setStyleSheet("text-align:left");
    ui->btnShow->setText(info);

    QString strIp = ip.split(":").at(0);
    QString port = ip.split(":").at(1);
    m_devModel = DeviceFactory::getDevice(type, strIp, port.toInt());

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&ControlForm::slot_timeout);
}

ControlForm::~ControlForm()
{
    delete ui;
}

void ControlForm::on_btnTrig_clicked()
{
    bool isChecked = ui->btnTrig->isChecked();
    if(isChecked)
    {
        m_timer->start(5000);
        ui->btnTrig->setIcon(QIcon(":/images/stop.png"));
    }
    else
    {
        if(m_timer->isActive())
        {
            m_timer->stop();
        }
        ui->btnTrig->setIcon(QIcon(":/images/start.png"));
    }

    m_devModel->autoTrig(isChecked);
}

void ControlForm::on_btnStatus_clicked()
{
    emit sig_btnStatus_click();
}

void ControlForm::on_btnShow_clicked()
{
    if(ui->btnShow->isChecked())
    {
        ui->groupBox_disp->setVisible(false);
        ui->btnShow->setIcon(QIcon(":/images/hide.png"));
    }
    else
    {
        ui->groupBox_disp->setVisible(true);
        ui->btnShow->setIcon(QIcon(":/images/show.png"));
    }
}

void ControlForm::slot_timeout()
{
    emit sig_update();
}

void ControlForm::setGrpVisible(bool value)
{
    ui->btnShow->setChecked(!value);
    if(value)
        ui->btnShow->setIcon(QIcon(":/images/show.png"));
    else
    {
        ui->btnShow->setIcon(QIcon(":/images/hide.png"));
    }
    ui->groupBox_disp->setVisible(value);
}

QString ControlForm::getInfo() const
{
    return m_info;
}
