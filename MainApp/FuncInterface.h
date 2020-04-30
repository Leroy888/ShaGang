#ifndef FUNCINTERFACE_H
#define FUNCINTERFACE_H

#include <QObject>

struct Data
{
    float volume;
    float area;
    float length;
    float width;
    float height;
    float weight;
};

class FuncInterface
{
public:
    FuncInterface() {}
    virtual ~FuncInterface() {}
    virtual QString getStrData() const = 0;
    virtual void setData(const QString &data) = 0;
    virtual void sendCmd(const QByteArray& cmd1, const QByteArray& cmd2) = 0;
    virtual Data getData() const = 0;

};


#define FuncInterface_iid "Examples.Plugin.FuncInterface"
Q_DECLARE_INTERFACE(FuncInterface, FuncInterface_iid)

#endif // FUNCINTERFACE_H
