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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    readJson();
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

/**
 * @brief MainWindow::populateMenus 根据插件生成menu
 * @param pluginInterface 插件
 * @param i 插件实现的接口
 */
void MainWindow::populateMenus(QObject * pluginInterface, UiInterface *i )
{
//    static auto menu = menuBar()->addMenu("功能");
//    auto act  = new QAction(i->name(),pluginInterface);
//    //单击menu调用插件
//    connect(act,&QAction::triggered,this,&MainWindow::slt_WidgetActionTriggered);
//    menu->addAction(act);
}

void MainWindow::readJson()
{
    QFile file("./cfg/menu.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"read json file failed";
        return;
    }
    QByteArray data = file.readAll();
    qDebug()<<"json data "<<QString(data);
    //QString strData = QString(data);
    file.close();

    QJsonParseError parseError;
    QJsonDocument jDoc(QJsonDocument::fromJson(data, &parseError));

    if(!(parseError.error == QJsonParseError::NoError))
    {
        qDebug()<<"parse json error:"<<parseError.errorString();
        return;
    }

    QJsonObject jObj = jDoc.object();
    QStringList keys = jObj.keys();
    qDebug()<<"root keys:"<<keys;
    if(keys.contains("button"))
    {
        QJsonArray array = jObj.value("button").toArray();
        for(int i=0; i<array.count(); i++)
        {
            QJsonValue value = array.at(i);
            if(value.isObject())
            {
                QJsonObject vObj = value.toObject();
                QStringList menuKeys = vObj.keys();
                foreach (QString mKey, menuKeys)
                {
                    QMenu *menu;
                    if(vObj.value(mKey).isString())
                    {
                        menu = ui->menuBar->addMenu(vObj.value(mKey).toString());
                    }
                    else if(vObj.value(mKey).isArray())
                    {
                        QJsonArray actionArray = vObj.value(mKey).toArray();
                        for(int j=0; j<actionArray.count(); j++)
                        {
                            if(actionArray.at(j).isObject())
                            {
                                QJsonObject actionObj = actionArray.at(j).toObject();
                                QAction *action = new QAction(actionObj.value("name").toString());
                                connect(action,&QAction::triggered,this,&MainWindow::slot_action_clicked);
                                menu->addAction(action);
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::slot_action_clicked()
{
    QAction *action =  (QAction*)sender();
    QString text = action->text();
    qDebug()<<"Action text "<<text;
    Form *form = new Form();

    setCentralWidget(form);
}

/**
 * @brief MainWindow::slt_WidgetActionTriggered 单击menu调用插件
 */
void MainWindow::slt_WidgetActionTriggered()
{
    auto centerWidget = qobject_cast<UiInterface*>(sender()->parent())->centerWidget();
    setCentralWidget(centerWidget);
}
