#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "../MainApp/FuncInterface.h"
#include "model/SerialPort.h"
#include "view/ClientForm.h"
#include <QMap>
#include "model/DeviceFactory.h"
#include "model/DeviceModel.h"
#include <QPushButton>
#include <QObject>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();

protected:
    void initTreeWidget();
private slots:
    void on_btnTurn_clicked();

    void on_cmbBox_turn_currentIndexChanged(int index);

    void slot_clicked(QWidget* wid);

    void on_btnSwitch_all_clicked();

    void slot_onBtnClicked();
    void slot_onBtnAll_clicked();
private:
    Ui::Form *ui;
    QWidget *m_curWidget;
    SerialPort *m_serialPort;
    FuncInterface *m_pInterface; 
    QString m_plugName;
    QString m_strCom;
    QString m_strDev;

    QStringList m_paramList;
    QMap<QString,QString> m_devIpMap;
    QMap<QString,ClientForm*> m_devFormMap;
    QMap<QString,QPushButton*> m_devBtnMap;

    DeviceModel *m_device;


private:
    void readIni();
    void initUi();
    void initLogic();
    bool loadPlugin();
    void updateUi();
};

#endif // FORM_H
