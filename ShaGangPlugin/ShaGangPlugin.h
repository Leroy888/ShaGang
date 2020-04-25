#ifndef SHAGANGPLUGIN_H
#define SHAGANGPLUGIN_H

#include <QObject>
#include "../MainApp/FuncInterface.h"

class ShaGangPlugin : public QObject, public FuncInterface
{
    Q_OBJECT
    Q_INTERFACES(FuncInterface)
    Q_PLUGIN_METADATA(IID FuncInterface_iid)
public:
    ShaGangPlugin();

    virtual QString getStrData() const override;
    virtual void setData(const QString &data) override;
    virtual void sendCmd(const QByteArray &cmd1, const QByteArray &cmd2) override;
    virtual Data getData() const override;

private:
    QString m_data;
};

#endif // SHAGANGPLUGIN_H
