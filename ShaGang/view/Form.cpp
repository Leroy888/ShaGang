#include "Form.h"
#include "ui_Form.h"

Form::Form(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}
