#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <QFrame>
#include "./model/DeviceModel.h"
#include "./model/DeviceFactory.h"
#include "./view/Frame.h"
#include "../MainApp/com/Functions.h"
#include "DataWidget.h"

namespace Ui {
class DataFrame;
}

class DataFrame : public Frame
{
    Q_OBJECT

public:
    explicit DataFrame(const SG_Data& data, Frame *parent = nullptr);
    ~DataFrame();

    virtual void setGrpVisible(bool value);
    virtual QString getInfo() const override;

public slots:
    void slot_updateData(const SG_Data &data);
private slots:
    void on_btnShow_clicked();

private:

    void initUi();
private:
    Ui::DataFrame *ui;
    SG_Data m_data;
    QList<DataWidget*> m_widgetList;
};

#endif // DATAFRAME_H
