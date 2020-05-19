#ifndef DATAFORM_H
#define DATAFORM_H

#include <QWidget>
#include "../MainApp/com/Functions.h"
#include <QLabel>
#include "DataWidget.h"
#include "Widget.h"

namespace Ui {
class DataForm;
}

class DataForm :  public Widget
{
    Q_OBJECT

public:
    explicit DataForm(const SG_Data& data, Widget *parent = nullptr);
    ~DataForm();

    virtual void setGrpVisible(bool value);
    virtual QString getInfo() const override;

public slots:
    void slot_updateData(const SG_Data &data);
private slots:
    void on_btnShow_clicked();

private:
    Ui::DataForm *ui;

    SG_Data m_data;
    QList<DataWidget*> m_widgetList;

private:

    void initUi();
};

#endif // DATAFORM_H
