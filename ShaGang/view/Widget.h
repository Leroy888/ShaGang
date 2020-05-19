#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = nullptr);

    virtual void setGrpVisible(const bool value) = 0;
    virtual QString getInfo() const = 0;

signals:

};

#endif // WIDGET_H
