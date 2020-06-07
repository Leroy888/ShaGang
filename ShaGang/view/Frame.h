#ifndef FRAME_H
#define FRAME_H

#include <QFrame>

class Frame : public QFrame
{
    Q_OBJECT
public:
    Frame(QFrame *parent = nullptr);

    virtual void setGrpVisible(const bool value) = 0;
    virtual QString getInfo() const = 0;
};

#endif // FRAME_H
