#ifndef STEELFORM_H
#define STEELFORM_H

#include <QWidget>

namespace Ui {
class SteelForm;
}

class SteelForm : public QWidget
{
    Q_OBJECT

public:
    explicit SteelForm(QWidget *parent = nullptr);
    ~SteelForm();

private:
    Ui::SteelForm *ui;
};

#endif // STEELFORM_H
