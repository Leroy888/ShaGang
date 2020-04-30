#ifndef COMMAND_H
#define COMMAND_H


#include <QByteArray>

class Command
{
public:
    Command();

    static QByteArray status();
    static QByteArray start();
    static QByteArray trig();
    static QByteArray autoTrig();
    static QByteArray stopTrig();
};

#endif // COMMAND_H
