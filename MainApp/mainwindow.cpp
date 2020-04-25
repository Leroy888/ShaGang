#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QPluginLoader>
#include <qdebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
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
        QObject *plugin = pluginLoader.instance();
        if(plugin)
        {
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
    static auto menu = menuBar()->addMenu("功能");
    auto act  = new QAction(i->name(),pluginInterface);
    //单击menu调用插件
    connect(act,&QAction::triggered,this,&MainWindow::slt_WidgetActionTriggered);
    menu->addAction(act);
}

/**
 * @brief MainWindow::slt_WidgetActionTriggered 单击menu调用插件
 */
void MainWindow::slt_WidgetActionTriggered()
{
    auto centerWidget = qobject_cast<UiInterface*>(sender()->parent())->centerWidget();
    setCentralWidget(centerWidget);
}
