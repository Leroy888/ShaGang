#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "UiInterface.h"

#include <QMainWindow>

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
private:
    void readJson();
private slots:
    void slt_WidgetActionTriggered();
private:
    Ui::MainWindow *ui;
    
    int loadPlugins();
};

#endif // MAINWINDOW_H
