#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>
#include "Widget.h"
#include "./model/DeviceModel.h"
#include "./model/DeviceFactory.h"
#include <QTimer>

namespace Ui {
class ControlForm;
}

class ControlForm :  public Widget
{
    Q_OBJECT

public:
    explicit ControlForm(const QString &info, const QString& type, const QString& ip, Widget *parent = nullptr);
    ~ControlForm();

    virtual void setGrpVisible(bool value);
    virtual QString getInfo() const override;
private slots:
    void on_btnTrig_clicked();

    void on_btnStatus_clicked();

    void on_btnShow_clicked();

    void slot_timeout();

signals:
    void sig_btnTrig_click();
    void sig_btnAuto_click(bool);
    void sig_btnStart_click();
    void sig_btnStatus_click();
    void sig_update();

private:
    Ui::ControlForm *ui;
    QString m_info;

    DeviceModel *m_devModel;
    QTimer* m_timer;
};

#endif // CONTROLFORM_H
