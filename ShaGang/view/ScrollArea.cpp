#include "ScrollArea.h"
#include "ui_ScrollArea.h"
#include "ControlForm.h"
#include "DataForm.h"


ScrollArea::ScrollArea(const QString &text, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrollArea)
{
    ui->setupUi(this);
    ui->btnShow->setStyleSheet("text-align:left");
    ui->btnShow->setText(text);
}

ScrollArea::~ScrollArea()
{
    delete ui;
}

void ScrollArea::addWidget(Widget *widget)
{
    ui->verticalLayout->addWidget(widget);
    m_formList.append(widget);
}

void ScrollArea::addWidget(Frame* frame)
{
    ui->verticalLayout->addWidget(frame);
    m_frameList.append(frame);
}

void ScrollArea::on_btnShow_clicked()
{
    if(ui->btnShow->isChecked())
    {
        ui->btnShow->setIcon(QIcon(":/images/hide.png"));
    }
    else
    {
        ui->btnShow->setIcon(QIcon(":/images/show.png"));
    }
    showForms(!ui->btnShow->isChecked());
}

void ScrollArea::showForms(const bool value)
{
    for (auto form : m_frameList) {
        form->setGrpVisible(value);
    }
}

void ScrollArea::setShow(const QString &info)
{
    for (auto form : m_frameList) {
        if(form->getInfo() != info)
            form->setGrpVisible(false);
        else
            form->setGrpVisible(true);
    }
}
