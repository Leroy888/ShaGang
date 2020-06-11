#ifndef CONTROLFRAME_H
#define CONTROLFRAME_H

#include <QFrame>
#include "./model/DeviceModel.h"
#include "./model/DeviceFactory.h"
#include "./view/Frame.h"
#include <QTimer>

namespace Ui {
class ControlFrame;
}

class ControlFrame : public Frame
{
    Q_OBJECT

public:
    explicit ControlFrame(const QString &type, const QString &dev, const QString &ip, const QString& plcIp, Frame *parent = nullptr);
    ~ControlFrame();

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
    Ui::ControlFrame *ui;

    QString m_info;

    DeviceModel *m_devModel;
    QTimer* m_timer;
};

#endif // CONTROLFRAME_H
