#include "ShaGangInterface.h"

#include <qpushbutton.h>
#include "window.h"
#include <iostream>

#include "qdebug.h"

using namespace std;

ShaGangInterface::ShaGangInterface()
{
    m_form = nullptr;
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

//QWidget *ShaGangInterface::centerWidget(QMap<QString, QString> &menuMap, QMap<QString, QStringList> &actionMap)
QWidget* ShaGangInterface::centerWidget(QList<MenuData*>& menuDataList, QMap<QString,QList<MenuData*>>& childMenuDataMap,
                              QMap<QString,QList<MenuData*>>& actionDataMap, QMap<int, QStringList>& toolBars)
{
    if(!m_form)
    {
        m_form = MainForm::getInstance();
        m_form->parseJson(menuDataList, childMenuDataMap, actionDataMap);
        toolBars = m_form->getToolBars();
    }

    return m_form;
}

void ShaGangInterface::zoomIn()
{
    if(m_form)
    {
       // m_form->zoomOut();
    }
}

void ShaGangInterface::zoomOut()
{
    if(m_form)
    {
      //  m_form->zoomOut();
        qDebug()<<"ShaGangInterface "<<__FUNCTION__;
    }
}

void ShaGangInterface::start()
{
    if(m_form)
    {

    }
}

void ShaGangInterface::executeCommand(const int cmd)
{

        qDebug()<<__FUNCTION__<<cmd;
        MainForm::getInstance()->executeCommand(cmd);

}
