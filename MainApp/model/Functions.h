#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QObject>
#include <QImage>
#include "FuncInterface.h"
#include "UiInterface.h"


enum IOStyle{
    ReadOnly,
    WriteOnly,
    ReadWrite,
    Appened
};

typedef QMap<QString,QMap<QString,int>> PosMap;
typedef QMap<QString,QList<double>> AiDataMap;


class Functions
{
public:
    Functions();

    static void sleepMs(int ms);
   // static bool loadPlugin(const QString &fileName, FuncInterface *interface);
    static bool loadPlugin(const QString &fileName, UiInterface *interface);
    static void mkDir(QString strPath);
    static QString stringListToString(const QStringList &list) ;

    static void saveImage(const QImage &img, const QString &savePath, const QString &imgName, const QString &pcInfo, const QString &strRes);
};

#endif // FUNCTIONS_H
