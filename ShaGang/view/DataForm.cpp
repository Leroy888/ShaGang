#include "DataForm.h"
#include "ui_DataForm.h"
#include <QSpacerItem>

DataForm::DataForm(const SG_Data& data, Widget *parent) :
    Widget(parent), ui(new Ui::DataForm), m_data(data)
{
    ui->setupUi(this);
    ui->btnShow->setStyleSheet("text-align:left");
    ui->btnShow->setText(data.info);
    initUi();
}

DataForm::~DataForm()
{
    delete ui;
}

void DataForm::setGrpVisible(bool value)
{
    ui->groupBox_disp->setVisible(value);
    ui->btnShow->setChecked(!value);
    if(value)
        ui->btnShow->setIcon(QIcon(":/images/show.png"));
    else
    {
        ui->btnShow->setIcon(QIcon(":/images/hide.png"));
    }
}

QString DataForm::getInfo() const
{
    return m_data.info;
}

void DataForm::initUi()
{
    m_widgetList.clear();

    QString text = QString(tr("体积："));
    double value = m_data.volume;
    QString unit = QString("m³");
    DataWidget* dw = new DataWidget(text, value, unit);
    ui->verticalLayout->addWidget(dw);
    m_widgetList.append(dw);

    text = QString(tr("面积："));
    value = m_data.area;
    unit = QString("m²");
    DataWidget* dwArea = new DataWidget(text, value, unit);
    ui->verticalLayout->addWidget(dwArea);
    m_widgetList.append(dwArea);

    text = QString(tr("长度："));
    value = m_data.length;
    unit = QString("m");
    DataWidget* dwLen = new DataWidget(text, value, unit);
    ui->verticalLayout->addWidget(dwLen);
    m_widgetList.append(dwLen);

    text = QString(tr("宽度："));
    value = m_data.width;
    unit = QString("m");
    DataWidget* dwWidth = new DataWidget(text, value, unit);
    ui->verticalLayout->addWidget(dwWidth);
    m_widgetList.append(dwWidth);

    text = QString(tr("高度："));
    value = m_data.height;
    unit = QString("m");
    DataWidget* dwHeight = new DataWidget(text, value, unit);
    ui->verticalLayout->addWidget(dwHeight);
    m_widgetList.append(dwHeight);

    ui->verticalLayout->addStretch();
  //  ui->verticalLayout->addSpacerItem(new QSpacerItem(10, 100, QSizePolicy::Expanding));
}

void DataForm::slot_updateData(const SG_Data& data)
{
    m_data = data;
    int i = 0;

    QString text = QString(tr("体积"));
    double value = m_data.volume;
    QString unit = QString("m³");

    m_widgetList.at(i++)->updateData(value);

    text = QString(tr("面积"));
    value = m_data.area;
    unit = QString("m²");
    m_widgetList.at(i++)->updateData(value);

    text = QString(tr("长度"));
    value = m_data.length;
    unit = QString("m");
    m_widgetList.at(i++)->updateData(value);

    text = QString(tr("宽度"));
    value = m_data.width;
    unit = QString("m");
    m_widgetList.at(i++)->updateData(value);

    text = QString(tr("高度"));
    value = m_data.height;
    unit = QString("m");
    m_widgetList.at(i++)->updateData(value);
}

void DataForm::on_btnShow_clicked()
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
