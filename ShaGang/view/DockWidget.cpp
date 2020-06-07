#include "DockWidget.h"

DockWidget::DockWidget(const QString &text)
{
    this->setMinimumWidth(168);
    initUi(text);
}

void DockWidget::initUi(const QString &text)
{
    m_scrollArea = new ScrollArea(text);
    this->setWidget(m_scrollArea);
}

void DockWidget::addWidget(Widget *widget)
{
    m_scrollArea->addWidget(widget);
}

void DockWidget::setShow(const QString &info)
{
    m_scrollArea->setShow(info);
}

void DockWidget::addWidget(Frame *frame)
{
    m_scrollArea->addWidget(frame);
}
