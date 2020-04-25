#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <qstring.h>
#include <QtPlugin>

class UiInterface
{
public:
    virtual ~UiInterface(){}
    virtual QString name() = 0;
    virtual QString information() = 0;
    virtual QWidget *centerWidget() = 0;    
};

#define UiInterface_iid "com.Interface.UiInterface"
Q_DECLARE_INTERFACE(UiInterface, UiInterface_iid)

#endif // MAININTERFACE_H
