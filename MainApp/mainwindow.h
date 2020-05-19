#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UiInterface.h"

#include <QMainWindow>
#include <QMap>
#include "com/Functions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void populateMenus(QObject *pluginInterface, UiInterface *i);

    void loadModel();
protected:
    void slot_action_clicked();
    bool loadPlugins(const QString &fileName);
private:
    void readJson();
    int loadPlugins();
private slots:
    void slt_WidgetActionTriggered();
private:
    Ui::MainWindow *ui;

    QWidget* m_curWidget;
    QAction* m_plugAction;

    QAction* m_backAction;
    QAction* m_nextAction;
    
    QMap<QString,QString> m_menuMap;
    QMap<QString,QStringList> m_actionMap;
    QList<QAction*> m_actionList;
    QList<QMenu*> m_menuList;
    QMap<QString,QMenu*> m_childMenuMap;

    QList<MenuData*> m_menuDataList;
    QMap<QString,QList<MenuData*>> m_childMenuDataMap;
    QMap<QString,QList<MenuData*>> m_actionDataMap;
};

#endif // MAINWINDOW_H
