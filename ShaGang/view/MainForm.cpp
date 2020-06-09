#include "MainForm.h"
#include "ui_MainForm.h"
#include "clsSettings.h"
#include "model/JsonReader.h"

#include <QDebug>


MainForm* MainForm::m_instance = nullptr;

MainForm::MainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainForm)
{
    ui->setupUi(this);

    qDebug()<<"MainForm ID "<<QThread::currentThreadId();

    readIni();
 //   g_ringBuffer = new CRingBuffer<Points3D>(g_nResolution);

    initUi();

    initLogic();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::slot_connected()
{
    qDebug()<<__FUNCTION__;
}

void MainForm::readIni()
{
    clsSettings *settings = new clsSettings("./cfg/Settings.ini");
    QString strNode = QString("System/");
    settings->readSetting(strNode + QString("funcPlug"), m_plugName);
    settings->readSetting(strNode + QString("strCom"), m_strCom);
    settings->readSetting(strNode + QString("strDev"), m_strDev);
    settings->readSetting(strNode + QString("strPort"), m_strPort);

    strNode = QString("ToolBar/");
    int barNum = 0;
    settings->readSetting(strNode + "toolBarNum", barNum);
    for(int i=0; i<barNum; i++)
    {
        QStringList bars;
        settings->readSetting(strNode + QString("toolBar_%1").arg(QString::number(i+1)), bars);
        m_toolBarMap.insert(i+1, bars);
    }

    strNode = QString("Device/");
    int devNum;
    settings->readSetting(strNode + "devNum", devNum);

    for(int i=0; i<devNum; i++)
    {
        QString strDev;
        settings->readSetting(strNode + QString("dev_%1").arg(QString::number(i + 1)), strDev);
        QString strIp;
        settings->readSetting(strNode + QString("ip_%1").arg(QString::number(i + 1)), strIp);
        m_devIpMap.insert(strDev, strIp);

        QString plcIp;
        settings->readSetting(strNode + QString("plcIp_%1").arg(QString::number(i + 1)), plcIp);
        m_plcIpMap.insert(strDev, plcIp);
    }

    strNode = QString("Param/");
    settings->readSetting(strNode + QString("paramList"), m_paramList);

    delete settings;
}

void MainForm::initUi()
{   
    QMap<QString,QString>::iterator it = m_devIpMap.begin();
    QStringList keys = m_devIpMap.keys();
    QString type= "Data";
    DockWidget* dw = new DockWidget("数据");
    QWidget* bar = dw->titleBarWidget();
    dw->setTitleBarWidget(new QWidget);
    delete bar;
    this->addDockWidget(Qt::RightDockWidgetArea, dw);
    m_dockList.append(dw);

    type = "Control";
    DockWidget* dw2 = new DockWidget("控制");
    QWidget* bar2 = dw2->titleBarWidget();
    dw2->setTitleBarWidget(new QWidget);
    delete bar2;
    this->addDockWidget(Qt::RightDockWidgetArea, dw2);
    m_dockList.append(dw2);

    QString style = "border-radius: 1px;border:1px solid black;background:#ffffff; color: rgb(18, 18, 18);font-size: 25px;";

    ui->gridLayout_client->setContentsMargins(2, 2, 2, 2);
    int num = 0;
    for(it; it != m_devIpMap.end(); it++, num++)
    {
        QString strDev = it.key();
        ClientForm *wdt = new ClientForm(strDev);
        wdt->setStyleSheet(style, false);

        SG_Data sgData;
        sgData.info = strDev;
        DataFrame* df = new DataFrame(sgData);
        dw->addWidget(df);
        connect(wdt,&ClientForm::sig_updateData,df,&DataFrame::slot_updateData);

        ControlFrame* cf = new ControlFrame(strDev, m_strDev, it.value(), m_plcIpMap.value(strDev));
        dw2->addWidget(cf);
        connect(cf,&ControlFrame::sig_update,wdt,&ClientForm::slot_update);

        m_devFormMap.insert(strDev, wdt);
        connect(wdt,SIGNAL(sig_clicked(QWidget*, QString&)),this,SLOT(slot_clicked(QWidget*, QString&)));
        connect(wdt,&ClientForm::sig_doubleClicked,this,&MainForm::slot_doubleClicked);

        ui->gridLayout_client->addWidget(wdt, num / 2, num % 2);
    }
}

void MainForm::initLogic()
{
    m_curWidget = nullptr;
    if(!m_devFormMap.isEmpty())
    {
        m_curWidget = m_devFormMap.begin().value();
    }
}

MainForm *MainForm::getInstance()
{
    if(!m_instance)
    {
        m_instance = new MainForm;
    }

    return m_instance;
}

void MainForm::parseJson(QList<MenuData *> &menuDataList, QMap<QString, QList<MenuData *> > &childMenuDataMap, QMap<QString,
                         QList<MenuData *> > &actionDataMap)
{
    JsonReader reader(QString("./cfg/cmd.txt"));
    reader.parseJson(menuDataList, childMenuDataMap, actionDataMap);
}

QMap<int, QStringList> MainForm::getToolBars() const
{
    return m_toolBarMap;
}

void MainForm::executeCommand(const int cmd)
{
    if(m_curWidget)
    {
        ClientForm* client = (ClientForm*)m_curWidget;
        client->executeCommand(cmd);
    }
}

void MainForm::slot_clicked(QWidget* wid, QString& info)
{
    m_curWidget = wid;
    m_info = info;
    updateUi();
}

void MainForm::updateUi()
{
    for (auto form : m_devFormMap)
    {
        if(m_curWidget == form)
        {
            QString style = "border-radius: 0px;border:2px solid rgb(248, 181, 0);background:#ffffff; color: rgb(18, 18, 18);font-size: 25px;";
            form->setStyleSheet(style, true);
        }
        else
        {
            QString style = "border-radius: 0px;border:1px solid black;background:rgb(102,102,102); color: rgb(18, 18, 18);font-size: 25px;";
            form->setStyleSheet(style, false);
        }
    }
}

void MainForm::slot_doubleClicked(QWidget *wid, QString &info, bool value)
{
    m_curWidget = wid;
    m_info = info;
    m_isClicked = value;

    for (auto form : m_devFormMap) {
        form->setVisible(!value);
    }

    for (auto dock : m_dockList) {
        dock->setShow(m_info);
    }

    if(value)
    {
        m_curWidget->setVisible(true);
    }
}
