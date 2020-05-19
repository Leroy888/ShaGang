#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <qstring.h>
#include <QtPlugin>
#include "com/Functions.h"

class UiInterface
{
public:
    virtual ~UiInterface(){}
    virtual QString name() = 0;
    virtual QString information() = 0;
    //virtual QWidget *centerWidget(QMap<QString,QString> &menuMap, QMap<QString,QStringList> &actionMap) = 0;
    virtual QWidget *centerWidget(QList<MenuData*>& menuDataList, QMap<QString,QList<MenuData*>>& childMenuDataMap,
                                  QMap<QString,QList<MenuData*>>& actionDataMap, QMap<int, QStringList>& toolBars) = 0;
    virtual void zoomOut() = 0;
    virtual void zoomIn() = 0;
    virtual void start() = 0;
    virtual void executeCommand(const int cmd) = 0;
};

#define UiInterface_iid "com.Interface.UiInterface"
Q_DECLARE_INTERFACE(UiInterface, UiInterface_iid)

#endif // MAININTERFACE_H
