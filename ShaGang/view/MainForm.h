#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QDockWidget>
#include "DockWidget.h"
#include "view/ClientForm.h"
#include "view/ControlForm.h"
#include "../MainApp/com/Functions.h"
#include "./model/TcpSocket.h"
#include "./view/DataForm.h"
#include "./view/ControlFrame.h"
#include "./view/DataFrame.h"

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

private:
    explicit MainForm(QWidget *parent = nullptr);
    ~MainForm();

    void readIni();
    void initUi();
    void initLogic();
public:
    static MainForm* getInstance();
    void parseJson(QList<MenuData*> &menuDataList, QMap<QString, QList<MenuData *>> &childMenuDataMap, QMap<QString, QList<MenuData *>> &actionDataMap);
    QMap<int, QStringList> getToolBars() const;
    void zoomOut();
    void executeCommand(const int cmd);


private slots:
    void slot_clicked(QWidget *wid, QString &info);
    void slot_doubleClicked(QWidget *wid, QString &info, bool value);
    void slot_connected();
private:
    Ui::MainForm *ui;

    QList<DockWidget*> m_dockList;
    QWidget *m_curWidget;
    QString m_info;
    QString m_plugName;
    QString m_strCom;
    QString m_strDev;

    QStringList m_paramList;
    QMap<QString,DeviceModel*> m_devModelMap;
    QMap<QString,QString> m_devIpMap;
    QMap<QString,ClientForm*> m_devFormMap;
  //  QMap<QString,QPushButton*> m_devBtnMap;
    QMap<QString,ControlForm*> m_devCtrlMap;
    QMap<QString,DataForm*> m_dataForm;
    QString m_strPort;
    QStringList m_shortcutMenus;
    QMap<int,QStringList> m_toolBarMap;

    bool m_isClicked;
    DeviceModel* m_devModel;

    QTcpSocket *m_socket;

    static MainForm* m_instance;
    void updateUi();
};

#endif // MAINFORM_H
