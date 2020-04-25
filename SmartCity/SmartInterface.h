#ifndef CENTERWIDGETTWO_H
#define CENTERWIDGETTWO_H

#include "centerwidgettwo_global.h"
#include "UiInterface.h"

class CENTERWIDGETTWOSHARED_EXPORT CenterWidgetTwo : public QObject ,public UiInterface
{
    Q_OBJECT
    Q_INTERFACES(UiInterface)
    Q_PLUGIN_METADATA(IID UiInterface_iid)
    
public:
    CenterWidgetTwo();
    ~CenterWidgetTwo();

    virtual QString name() override;
    virtual QString information() override;
    virtual QWidget *centerWidget() override;
};

#endif // CENTERWIDGETTWO_H
