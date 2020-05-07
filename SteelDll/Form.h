#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "../MainApp/FuncInterface.h"
#include "view/ClientForm.h"
#include <QMap>
#include <QPushButton>
#include <QObject>
#include "view/ControlForm.h"

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

    void slot_clicked(QWidget* wid, QString &info);
    void slot_doubleClicked(QWidget* wid, QString &info, bool value);

    void on_btnSwitch_all_clicked();

    void slot_onBtnClicked();
    void slot_onBtnAll_clicked();
    void on_btnShow_clicked();

    void slot_onBtnStart_clicked();
    void slot_onBtnAutoClicked(bool value);
    void slot_onBtnTrig_clicked();
    void slot_onBtnStatus_clicked();
private:
    Ui::Form *ui;
    QWidget *m_curWidget;
    QString m_info;
    FuncInterface *m_pInterface; 
    QString m_plugName;
    QString m_strCom;
    QString m_strDev;

    QStringList m_paramList;
    QMap<QString,QString> m_devIpMap;
    QMap<QString,ClientForm*> m_devFormMap;
    QMap<QString,QPushButton*> m_devBtnMap;
    QMap<QString,ControlForm*> m_devCtrlMap;
    QString m_strPort;

    bool m_isClicked;


private:
    void readIni();
    void initUi();
    void initLogic();
    bool loadPlugin();
    void updateUi();
};

#endif // FORM_H
