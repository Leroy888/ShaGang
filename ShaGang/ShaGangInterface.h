#ifndef CENTERWIDGETONE_H
#define CENTERWIDGETONE_H

#include "ShaGang_global.h"
#include "UiInterface.h"
#include "view/MainForm.h"
class CENTERWIDGETONESHARED_EXPORT ShaGangInterface : public QObject, public UiInterface
{
    Q_OBJECT
    Q_INTERFACES(UiInterface)
    Q_PLUGIN_METADATA(IID UiInterface_iid)
    
public:
    ShaGangInterface();
    ~ShaGangInterface();
    
    virtual QString name() override;
    virtual QString information() override;
    virtual QWidget *centerWidget(QList<MenuData*>& menuDataList, QMap<QString,QList<MenuData*>>& childMenuDataMap,
                                  QMap<QString,QList<MenuData*>>& actionDataMap, QMap<int, QStringList> &toolBars) override;
    virtual void zoomIn() override;
    virtual void zoomOut() override;
    virtual void start() override;
    virtual void executeCommand(const int cmd) override;

private:
    MainForm* m_form;

};

#endif // CENTERWIDGETONE_H
