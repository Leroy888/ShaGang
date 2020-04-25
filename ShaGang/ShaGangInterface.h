#ifndef CENTERWIDGETONE_H
#define CENTERWIDGETONE_H

#include "ShaGang_global.h"
#include "UiInterface.h"
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
    virtual QWidget *centerWidget() override;
};

#endif // CENTERWIDGETONE_H
