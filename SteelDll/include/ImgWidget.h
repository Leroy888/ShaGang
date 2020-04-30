#ifndef IMGWIDGET_H
#define IMGWIDGET_H

#include <QObject>
#include <QOpenGLWidget>
#include <QMouseEvent>

class ImgWidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    ImgWidget();

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void clicked();

};

#endif // IMGWIDGET_H
