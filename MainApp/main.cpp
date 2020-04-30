#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QMutex>
#include <QDateTime>

#include <QDebug>

#define LOG_FILE qApp->applicationDirPath() + QString("/log/%1_logger.txt").arg(QDate::currentDate().toString("yyyyMMdd"))

void loggerOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch (type) {
    case QtDebugMsg:
        text = QString("Info: ");
        break;
    default:
        break;
    }

    QString curDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString message = QString("%1 %2%3").arg(curDate).arg(text).arg(msg);
    QFile file(LOG_FILE);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream textStream(&file);
    textStream<<message<<"\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(loggerOutput);

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
