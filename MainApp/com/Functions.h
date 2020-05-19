#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QStringList>

struct MenuData
{
    QString CN_menu;
    QString EN_menu;
    QString cmd;
    int     cmd_id;
    bool    enabled;
    QString shortcut;
    QString icon;
};

struct SG_Data
{
    QString info;
    double volume;
    double area;
    double weight;
    double length;
    double width;
    double height;
};

class Functions
{
public:
    Functions();
};

#endif // FUNCTIONS_H
