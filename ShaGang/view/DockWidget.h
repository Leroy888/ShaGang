#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>
#include <QVBoxLayout>
#include "ScrollArea.h"

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    DockWidget(const QString &text);

    void initUi(const QString &text);

    void addWidget(Widget *widget);

    void setShow(const QString& info);

private:
    ScrollArea* m_scrollArea;
};

#endif // DOCKWIDGET_H
