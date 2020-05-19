#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QWidget>
#include "../MainApp/com/Functions.h"
#include "DataForm.h"
#include "Widget.h"

namespace Ui {
class ScrollArea;
}

class ScrollArea : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollArea(const QString &text, QWidget *parent = nullptr);
    ~ScrollArea();

    void addWidget(Widget *widget);
    void showForms(const bool value);
    void setShow(const QString& info);
private slots:
    void on_btnShow_clicked();

private:

    QList<Widget*> m_formList;
protected:
    Ui::ScrollArea *ui;
};

#endif // SCROLLAREA_H
