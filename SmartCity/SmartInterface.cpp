#include "SmartInterface.h"
#include "qdebug.h"
#include <QPushButton>

CenterWidgetTwo::CenterWidgetTwo()
{
}

CenterWidgetTwo::~CenterWidgetTwo()
{
    qDebug()<<"~CenterWidgetTwo";
}


QString CenterWidgetTwo::name()
{
    return "智慧城市";
}

QString CenterWidgetTwo::information()
{
    return "SmartCity_info";
}

QWidget *CenterWidgetTwo::centerWidget()
{
    auto btn = new QPushButton("智慧城市");
    return  btn;
}
