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
#include "FormManager.h"
#include "JsonReader.h"
#include "Command.h"
#include <QThread>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  readJson();
    loadPlugins();

    m_curWidget = nullptr;
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
        if(!fileName.endsWith("dll"))
            continue;

        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
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
    m_plugAction = act;
    menu->menuAction()->setVisible(false);
}

void MainWindow::loadModel()
{
    m_plugAction->trigger();    //做成配置
}

void MainWindow::readJson()
{

}

void MainWindow::slot_action_clicked()
{
    QAction *action = (QAction*)sender();
    QString text = action->text();
    qDebug()<<__FUNCTION__<<text;
    int cmd_id;

    for(auto dataList : m_actionDataMap)
    {
        for (auto data : dataList) {
            if(data->CN_menu == text){
                cmd_id = data->cmd_id;
                if(cmd_id == 1000)
                {
                    qApp->exit();
                }
                qobject_cast<UiInterface*>(sender()->parent())->executeCommand(cmd_id);
                return;
            }
        }
    }
}

/**
 * @brief MainWindow::slt_WidgetActionTriggered 单击menu调用插件
 */
void MainWindow::slt_WidgetActionTriggered()
{ 
    QMap<int, QStringList> toolBars;
    auto widget = qobject_cast<UiInterface*>(sender()->parent())->centerWidget(m_menuDataList, m_childMenuDataMap, m_actionDataMap, toolBars);
    if(widget == m_curWidget)
    {
        return;
    }

    m_curWidget = widget;
    if(!widget)
    {
        qDebug()<<"load MainForm dll failed";
    }
    qDebug()<<"MainWindow ID "<<QThread::currentThreadId();

    this->removeToolBar(ui->mainToolBar);
    QToolBar* mainToolBar = new QToolBar();
    mainToolBar->setIconSize(QSize(24, 24));
    mainToolBar->setFixedHeight(40);
    this->addToolBar(mainToolBar);
    QAction* mainSpt = mainToolBar->addSeparator();

    mainSpt->setIcon(QIcon(":/images/back.png"));
    mainSpt->setSeparator(true);
    m_backAction = mainToolBar->addAction(QIcon(":/images/back.png"), "返回");
    m_nextAction = mainToolBar->addAction(QIcon(":/images/next.png"), "向前");

    QList<QToolBar*> toolBarList;
    for (int i=0; i<toolBars.count(); i++)
    {
        QToolBar* toolBar = new QToolBar();
        this->addToolBar(toolBar);
        QAction* spt = toolBar->addSeparator();
        spt->setIcon(QIcon(":/images/blackLine.png"));
        toolBarList.append(toolBar);
    }

    for (auto data : m_menuDataList) {
        QMenu *menu = this->menuBar()->addMenu(data->CN_menu);
        QString cnText = data->CN_menu;
        QList<MenuData*> childData = m_childMenuDataMap.value(cnText);

        QStringList ctnList;
        if(!childData.isEmpty())
        {
            for (auto cData : childData) {
                QString childText = cData->CN_menu;

                QList<MenuData*> actionDataList = m_actionDataMap.value(cData->CN_menu);
                QMenu *childMenu = menu->addMenu(childText);
                for (auto actData : actionDataList) {
                    QAction *action = new QAction(actData->CN_menu, sender()->parent());
                    action->setEnabled(actData->enabled);
                    connect(action,&QAction::triggered,this,&MainWindow::slot_action_clicked);
                    if(actData->shortcut != "")
                    {
                        action->setShortcut(actData->shortcut);
                    }
                    childMenu->addAction(action);
                    ctnList.append(actData->CN_menu);
                    //添加快捷菜单
                    for (int var = 0; var < toolBars.count(); ++var) {
                        QStringList barActions = toolBars.value(var+1);
                        if(barActions.contains(actData->CN_menu))
                        {
                            QAction* scAction = toolBarList.at(var)->addAction(actData->CN_menu);
                            scAction->setParent(sender()->parent());
                            scAction->setIcon(QIcon(actData->icon));
                            connect(scAction,&QAction::triggered,this,&MainWindow::slot_action_clicked);
                        }
                    }
                }
            }
        }

        QList<MenuData*> actionDataList = m_actionDataMap.value(cnText);
        for (auto actData : actionDataList) {
            if(!ctnList.contains(actData->CN_menu))
            {
                QAction *action = new QAction(actData->CN_menu, sender()->parent());
                action->setEnabled(actData->enabled);
                connect(action,&QAction::triggered,this,&MainWindow::slot_action_clicked);
                if(actData->shortcut != "")
                {
                    action->setShortcut(actData->shortcut);
                }
                menu->addAction(action);
                //添加快捷菜单
                for (int var = 0; var < toolBars.count(); ++var) {
                    QStringList barActions = toolBars.value(var+1);
                    if(barActions.contains(actData->CN_menu))
                    {
                        QAction* scAction = toolBarList.at(var)->addAction(actData->CN_menu);
                        scAction->setParent(sender()->parent());
                        scAction->setIcon(QIcon(actData->icon));
                        connect(scAction,&QAction::triggered,this,&MainWindow::slot_action_clicked);
                    }
                }
            }
        }
    }

    setCentralWidget(widget);
}
