#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UiInterface.h"

#include <QMainWindow>
#include <QMap>

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
    
    QMap<QString,QString> m_pluginMap;
    QMap<QString,QStringList> m_menuMap;
};

#endif // MAINWINDOW_H
