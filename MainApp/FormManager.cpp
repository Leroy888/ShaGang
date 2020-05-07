#include "FormManager.h"

FormManager::FormManager()
{

}

QWidget *FormManager::getForm(const QString &text)
{
    if(text == QString("ShaGang.dll") || text == QString("沙钢"))
    {
        return new Form;
    }
    else
    {
        return (QWidget*) nullptr;
    }
}
