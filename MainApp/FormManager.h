#ifndef FORMMANAGER_H
#define FORMMANAGER_H

#include <QWidget>
#include "Form.h"

class FormManager
{
public:
    FormManager();

    static QWidget* getForm(const QString &text);
};

#endif // FORMMANAGER_H
