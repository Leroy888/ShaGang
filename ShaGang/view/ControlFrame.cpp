#include "ControlFrame.h"
#include "ui_ControlFrame.h"

ControlFrame::ControlFrame(const QString &info, const QString &type, const QString &ip, const QString &plcIp, Frame *parent) :
    Frame(parent),
    ui(new Ui::ControlFrame), m_info(info)
{
    ui->setupUi(this);

    ui->btnShow->setStyleSheet("text-align:left");
    ui->btnShow->setText(info);

    QString strIp = ip.split(":").at(0);
    QString port = ip.split(":").at(1);
    m_devModel = DeviceFactory::getDevice(type, strIp, port.toInt(), plcIp);
    connect(m_devModel,&DeviceModel::sig_reloadData,this,&ControlFrame::slot_timeout);

    m_timer = new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&ControlFrame::slot_timeout);
}

ControlFrame::~ControlFrame()
{
    delete ui;
}


void ControlFrame::on_btnTrig_clicked()
{
    bool isChecked = ui->btnTrig->isChecked();
    if(isChecked)
    {
      //  m_timer->start(60000);
        ui->btnTrig->setText(QStringLiteral("停止"));
        ui->btnTrig->setIcon(QIcon(":/images/stop.png"));
    }
    else
    {
        if(m_timer->isActive())
        {
            m_timer->stop();
        }
        ui->btnTrig->setText(QStringLiteral("触发"));
        ui->btnTrig->setIcon(QIcon(":/images/start.png"));
    }

    m_devModel->autoTrig(isChecked);
}

void ControlFrame::on_btnStatus_clicked()
{
    emit sig_btnStatus_click();
}

void ControlFrame::on_btnShow_clicked()
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

void ControlFrame::slot_timeout()
{
    emit sig_update();
    qDebug()<<"ControlFrame "<<__FUNCTION__;
}

void ControlFrame::setGrpVisible(bool value)
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

QString ControlFrame::getInfo() const
{
    return m_info;
}

