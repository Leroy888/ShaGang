#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QWidget>
#include <QTcpSocket>
#include <QMouseEvent>
#include "../MainApp/com/Functions.h"

namespace Ui {
class ClientForm;
}

class ClientForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientForm(QString &strDev, QWidget *parent = nullptr);
    ~ClientForm();

    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent *event);

    void setInfo(const QString info);
    QString getInfo() const;
    void setStyleSheet(const QString &styleSheet, bool value);

    void connectToHost();

     void executeCommand(const int cmd);

signals:
    void sig_clicked(QWidget*, QString&);
    void sig_doubleClicked(QWidget*, QString&, bool);
    void sig_updateData(const SG_Data &data);

public slots:
    void slot_update();
private slots:
    void slot_clicked(QString &info);
    void slot_doubleClicked(QString &info, bool value);

private:
    Ui::ClientForm *ui;

    QString m_strDev;
    bool m_isClicked;
};

#endif // CLIENTFORM_H
