#include "DataWidget.h"
#include "ui_DataWidget.h"

DataWidget::DataWidget(const QString &text, const double value, const QString &unit, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataWidget)
{
    ui->setupUi(this);

    ui->label_disp->setText(text);
    ui->label_value->setText(QString::number(value));
    ui->label_unit->setText(unit);
}

DataWidget::~DataWidget()
{
    delete ui;
}

void DataWidget::updateData(const double value)
{
    ui->label_value->setText(QString::number(value));
}
