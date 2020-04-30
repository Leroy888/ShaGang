#ifndef CONTROLFORM_H
#define CONTROLFORM_H

#include <QWidget>

namespace Ui {
class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(const QString &info, QWidget *parent = nullptr);
    ~ControlForm();

private slots:
    void on_btnTrig_clicked();

    void on_btnAuto_clicked();

    void on_btnStart_clicked();

    void on_btnStatus_clicked();

signals:
    void sig_btnTrig_click();
    void sig_btnAuto_click(bool);
    void sig_btnStart_click();
    void sig_btnStatus_click();

private:
    Ui::ControlForm *ui;
};

#endif // CONTROLFORM_H
