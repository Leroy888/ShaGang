#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QPluginLoader>
#include <qdebug.h>
#include "../ShaGang/clsSettings.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>
#include "../SteelDll/Form.h"
#include "FormManager.h"
#include "JsonReader.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
  //  readJson();
    loadPlugins();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::loadPlugins 加载插件、插件放在plugins文件夹下
 * @return 返回插件的个数
 */
int MainWindow::loadPlugins()
{
    int count  = 0;
    QDir pluginsDir = QDir(qApp->applicationDirPath());
    if(!pluginsDir.cd("plugins")) return -1;
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        qDebug()<<"fileName "<<fileName;
        QObject *plugin = pluginLoader.instance();
        if(plugin)
        {
            qDebug()<<"load fileName "<<fileName;
            auto centerInterface = qobject_cast<UiInterface*>(plugin);
            if(centerInterface)
            {
                ++count;
                //加载插件后生成menu
                populateMenus(plugin,centerInterface);
            }
        }
    } 
    return count;
}

bool MainWindow::loadPlugins(const QString &fileName)
{
    QPluginLoader loader(QString("./plugins/%1").arg(fileName));
    QObject *plugin = loader.instance();
    if(plugin)
    {
        auto centerInterface = qobject_cast<UiInterface*>(plugin);
        if(centerInterface)
        {

        }
    }

    return false;
}

/**
 * @brief MainWindow::populateMenus 根据插件生成menu
 * @param pluginInterface 插件
 * @param i 插件实现的接口
 */
void MainWindow::populateMenus(QObject * pluginInterface, UiInterface *i )
{
    static auto menu = menuBar()->addMenu("功能");
    auto act  = new QAction(i->name(),pluginInterface);
    //单击menu调用插件
    connect(act,&QAction::triggered,this,&MainWindow::slt_WidgetActionTriggered);
    menu->addAction(act);
}

void MainWindow::readJson()
{
    JsonReader reader("./cfg/menu.txt");
    reader.parseJson(m_menuMap, m_pluginMap);

    QMap<QString,QStringList>::iterator it;
    for(it=m_menuMap.begin(); it != m_menuMap.end(); it++)
    {
        qDebug()<<it.key()<<" "<<it.value();
        QMenu *menu = this->menuBar()->addMenu(it.key());
        //QMenu *m = menu->addMenu("Test");

        for(int i=0; i<it.value().length(); i++)
        {
            QAction *action = new QAction(it.value().at(i));
            connect(action,&QAction::triggered,this,&MainWindow::slot_action_clicked);
            menu->addAction(action);
        }
    }
}

void MainWindow::slot_action_clicked()
{
    QAction *action =  (QAction*)sender();
    QString text = action->text();
    qDebug()<<"Action text "<<text;

    QString fileName = m_pluginMap.value(text);
    fileName = QString("ShaGang.dll");
    QWidget *form = FormManager::getForm(fileName);

    if(form)
    {
        setCentralWidget(form);
    }
  //  setCentralWidget(form);
}

/**
 * @brief MainWindow::slt_WidgetActionTriggered 单击menu调用插件
 */
void MainWindow::slt_WidgetActionTriggered()
{
   // QAction *action = new QAction()
    auto centerWidget = qobject_cast<UiInterface*>(sender()->parent())->centerWidget();
    setCentralWidget(centerWidget);
}
