#include "SteelForm.h"
#include "ui_SteelForm.h"

SteelForm::SteelForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SteelForm)
{
    ui->setupUi(this);
}

SteelForm::~SteelForm()
{
    delete ui;
}
