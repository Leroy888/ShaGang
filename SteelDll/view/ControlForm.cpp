#include "ControlForm.h"
#include "ui_ControlForm.h"
#include "com/Command.h"

ControlForm::ControlForm(const QString &info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    ui->setupUi(this);
    ui->label->setText(info);
}

ControlForm::~ControlForm()
{
    delete ui;
}

void ControlForm::on_btnTrig_clicked()
{
    emit sig_btnTrig_click();
}

void ControlForm::on_btnAuto_clicked()
{
    bool isChecked = ui->btnAuto->isChecked();
    if(isChecked)
    {
        ui->btnAuto->setIcon(QIcon(":/images/stop.ico"));
    }
    else
    {
        ui->btnAuto->setIcon(QIcon(":/images/start.ico"));
    }
    emit sig_btnAuto_click(isChecked);
}

void ControlForm::on_btnStart_clicked()
{
    emit sig_btnStart_click();
}

void ControlForm::on_btnStatus_clicked()
{
    emit sig_btnStatus_click();
}
