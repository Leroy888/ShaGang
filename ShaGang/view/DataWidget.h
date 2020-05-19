#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>

namespace Ui {
class DataWidget;
}

class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(const QString& text, const double value, const QString& unit, QWidget *parent = nullptr);
    ~DataWidget();

    void updateData(const double value);

private:
    Ui::DataWidget *ui;
};

#endif // DATAWIDGET_H
