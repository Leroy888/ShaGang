#include "ShaGangInterface.h"

#include <qpushbutton.h>
#include "Form.h"
#include "window.h"
#include <iostream>

#include "qdebug.h"

using namespace std;

ShaGangInterface::ShaGangInterface()
{
}

ShaGangInterface::~ShaGangInterface()
{
    qDebug()<<"~ShaGangInterface";
}

QString ShaGangInterface::name()
{
    return "沙钢";
}

QString ShaGangInterface::information()
{
    return "ShaGang_info";
}

QWidget *ShaGangInterface::centerWidget()
{
  //  Window* form = new Window();
    Form *form = new Form;
    return form;
}
