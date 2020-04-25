#include "mainwindow.h"
#include <QApplication>
#include <QFile>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/qss/style.qss");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Read qss file failed";
    }
    else
    {
        a.setStyleSheet(file.readAll());
    }

    MainWindow w;
    w.show();
    
    return a.exec();
}
