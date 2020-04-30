#include "Form.h"
#include "ui_Form.h"
#include <QDir>
#include <QPluginLoader>
#include <../MainApp/FuncInterface.h>
#include "clsSettings.h"
#include <QLabel>
#include <QTableWidgetItem>
#include <QTreeWidgetItem>
#include <QTreeWidgetItemIterator>
#include <QMessageBox>


#include <QDebug>

#define ROW 2
#define COLUMN 2

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    readIni();

    // const QString fileName = QString("./funcPlugins/%1").arg(m_plugName);
    if(!loadPlugin())
    {
        qDebug()<<"Load funcPlugin failed";
    }
    initUi();

    initLogic();
    m_curWidget = nullptr;
}

Form::~Form()
{
    delete ui;
}

void Form::readIni()
{
    clsSettings *settings = new clsSettings("./cfg/Settings.ini");
    QString strNode = QString("System/");
    settings->readSetting(strNode + QString("funcPlug"), m_plugName);
    settings->readSetting(strNode + QString("strCom"), m_strCom);
    settings->readSetting(strNode + QString("strDev"), m_strDev);

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
    }

    strNode = QString("Param/");
    settings->readSetting(strNode + QString("paramList"), m_paramList);

    delete settings;
}

bool Form::loadPlugin()
{
    const QString fileName = QString("./funcPlugins/%1").arg(m_plugName);

    QPluginLoader loader(fileName);
    QObject *plugin = loader.instance();
    if(plugin)
    {
        m_pInterface = qobject_cast<FuncInterface*> (plugin);
        if(m_pInterface)
        {
            return true;
        }
    }

    return false;
}

void Form::initUi()
{
    QMap<QString,QString>::iterator it = m_devIpMap.begin();
    QString style = "border-radius: 1px;border:1px solid black;background:#ffffff; color: rgb(18, 18, 18);font-size: 25px;";

    int num = 0;
    for(it; it != m_devIpMap.end(); it++, num++)
    {
        QString strDev = it.key();
        ClientForm *wdt = new ClientForm(it.value(), 2111, m_strDev);
        wdt->setInfo(strDev);
        wdt->setStyleSheet(style, false);
        wdt->connectToHost();

        m_devFormMap.insert(strDev, wdt);
        connect(wdt,SIGNAL(sig_clicked(QWidget*, QString&)),this,SLOT(slot_clicked(QWidget*, QString&)));

        QLabel *label = new QLabel(strDev);
        QPushButton *btn = new QPushButton(it.key());
        btn->setIcon(QIcon(":/images/start.ico"));
        btn->setCheckable(true);
        connect(btn,&QPushButton::clicked,this,&Form::slot_onBtnClicked);
        m_devBtnMap.insert(strDev, btn);

        ControlForm *ctrl = new ControlForm(strDev);
        connect(ctrl,&ControlForm::sig_btnAuto_click,this,&Form::slot_onBtnAutoClicked);
        connect(ctrl,&ControlForm::sig_btnStart_click,this,&Form::slot_onBtnStart_clicked);
        connect(ctrl,&ControlForm::sig_btnStatus_click,this,&Form::slot_onBtnStatus_clicked);
        connect(ctrl,&ControlForm::sig_btnTrig_click,this,&Form::slot_onBtnTrig_clicked);
        m_devCtrlMap.insert(strDev, ctrl);

        ui->verLayout_ctrl->addWidget(ctrl);

        ui->gridLayout_client->addWidget(wdt, num / 2, num % 2);
    }

    if(m_devIpMap.count() > 0)
    {
        QLabel *label = new QLabel(QString("全部"));
        QPushButton *btn = new QPushButton(QString("全部"));
        btn->setIcon(QIcon(":/images/start.ico"));
        btn->setCheckable(true);
        connect(btn,&QPushButton::clicked,this,&Form::slot_onBtnAll_clicked);
        m_devBtnMap.insert(QString("all"), btn);
    }

    initTreeWidget();
}

void Form::initTreeWidget()
{
    QStringList headers;
    headers<<QString("名称")<<QString("数据");
    ui->treeWidget->setHeaderLabels(headers);
    ui->treeWidget->setColumnCount(2);
    QStringList keys = m_devIpMap.keys();
    foreach (QString dev, keys)
    {
        QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
        root->setText(0, dev);
        root->setTextAlignment(0, Qt::AlignCenter);
        root->setTextColor(0, Qt::blue);
        root->setBackgroundColor(0, Qt::black);
        root->setBackgroundColor(1, QColor(111, 156, 207));
        root->setBackground(0, QBrush(Qt::black));

        foreach (QString text, m_paramList)
        {
            QTreeWidgetItem *item1 = new QTreeWidgetItem(root);
            item1->setText(0, text);
        }
    }

    ui->treeWidget->expandAll();
}

void Form::updateUi()
{
    QMap<QString,ClientForm*>::iterator it;

    int num = 0;
    for(it = m_devFormMap.begin(); it != m_devFormMap.end(); it++)
    {
        num++;
        if(m_curWidget == it.value())
        {
           QString style = "border-radius: 1px;border:3px solid red;background:#ffffff; color: rgb(18, 18, 18);font-size: 25px;";
           it.value()->setStyleSheet(style, true);
        }
        else
        {
            QString style = "border-radius: 1px;border:1px solid black;background:#ffffff; color: rgb(18, 18, 18);font-size: 25px;";
            it.value()->setStyleSheet(style, false);
        }
    }

    qDebug()<<__FUNCTION__;
}

void Form::initLogic()
{

}

void Form::slot_onBtnClicked()
{
    QPushButton *btn = (QPushButton*) sender();
    QString strDev = m_devBtnMap.key(btn);
    ClientForm *form = m_devFormMap.value(strDev);
    if(btn->isChecked())
    {
        btn->setIcon(QIcon(":/images/stop.ico"));
        if(form)
        {
            form->start();
        }
    }
    else
    {
        btn->setIcon(QIcon(":/images/start.ico"));
        if(form)
        {
            form->stop();
        }
    }
}

void Form::slot_onBtnAll_clicked()
{
    QPushButton *btn = (QPushButton*) sender();
    bool isChecked = btn->isChecked();
    if(btn->isChecked())
    {
        btn->setIcon(QIcon(":/images/stop.ico"));
    }
    else
    {
        btn->setIcon(QIcon(":/images/start.ico"));
    }

    foreach (QPushButton* btns, m_devBtnMap)
    {
        if(btn != btns && btns->isChecked() != isChecked)
        {
            btns->click();
        }
    }
}

void Form::slot_onBtnStart_clicked()
{
    ControlForm *ctrl = (ControlForm*) sender();
    QString strDev = m_devCtrlMap.key(ctrl);
    ClientForm *client = m_devFormMap.value(strDev);
    if(client)
    {
        client->start();
    }
}

void Form::slot_onBtnAutoClicked(bool value)
{
    ControlForm *ctrl = (ControlForm*) sender();
    QString strDev = m_devCtrlMap.key(ctrl);
    ClientForm *client = m_devFormMap.value(strDev);
    if(client)
    {
        client->autoTrig(value);
    }
}

void Form::slot_onBtnTrig_clicked()
{
    ControlForm *ctrl = (ControlForm*) sender();
    QString strDev = m_devCtrlMap.key(ctrl);
    ClientForm *client = m_devFormMap.value(strDev);
    if(client)
    {
        client->trig();
    }
}

void Form::slot_onBtnStatus_clicked()
{
    ControlForm *ctrl = (ControlForm*) sender();
    QString strDev = m_devCtrlMap.key(ctrl);
    ClientForm *client = m_devFormMap.value(strDev);
    if(client)
    {
        client->status();
    }
}

void Form::on_btnTurn_clicked()
{
    QString text = ui->lineEdit->text();
    m_pInterface->setData(text);
    QString tText = m_pInterface->getStrData();
    ui->lineEdit_2->setText(tText);
    m_pInterface->sendCmd(QString("Fuck").toLatin1(), QString("Luck").toLatin1());
}

void Form::on_cmbBox_turn_currentIndexChanged(int index)
{
    if(index == 0)
    {
        QMap<QString,ClientForm*>::iterator it = m_devFormMap.begin();
        for(it; it!=m_devFormMap.end(); it++)
        {
            it.value()->setVisible(false);
        }
        m_curWidget->setVisible(true);
    }
    else
    {
        QMap<QString,ClientForm*>::iterator it = m_devFormMap.begin();
        for(it; it!=m_devFormMap.end(); it++)
        {
            it.value()->setVisible(true);
        }
    }
}


void Form::slot_clicked(QWidget *wid, QString& info)
{
    m_curWidget = wid;
    m_info = info;
    updateUi();
    qDebug()<<"Form slot_clicked";
}

void Form::on_btnSwitch_all_clicked()
{

}

void Form::on_btnShow_clicked()
{
    if(!m_curWidget)
    {
        QMessageBox::warning(this, tr("提示"), tr("选择窗口"), QMessageBox::Ok);
        ui->btnShow->setChecked(!ui->btnShow->isChecked());
        return;
    }
    if(ui->btnShow->isChecked())
    {
        ui->btnShow->setText(tr("显示全部"));
        QTreeWidgetItemIterator it(ui->treeWidget);
        while(*it)
        {
            if((*it)->text(0) != (m_info))
                (*it)->setExpanded(false);
            it++;
        }

        QMap<QString,ClientForm*>::iterator itt = m_devFormMap.begin();
        for(itt; itt!=m_devFormMap.end(); itt++)
        {
            itt.value()->setVisible(false);
        }
        m_curWidget->setVisible(true);
    }
    else
    {
        ui->btnShow->setText(tr("显示选中"));
        QTreeWidgetItemIterator it(ui->treeWidget);
        while(*it)
        {
            (*it)->setExpanded(true);
            it++;
        }

        QMap<QString,ClientForm*>::iterator itt = m_devFormMap.begin();
        for(itt; itt!=m_devFormMap.end(); itt++)
        {
            itt.value()->setVisible(true);
        }
    }
}
