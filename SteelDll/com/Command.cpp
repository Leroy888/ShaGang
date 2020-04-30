#include "Command.h"

Command::Command()
{

}

QByteArray Command::status()
{
    QByteArray cmd;
    // HEX: 02 73 52 4E 20 53 54 6C 6D 73 03
    cmd.append(0x02);
    cmd.append(0x73);
    cmd.append(0x52);
    cmd.append(0x4E);
    cmd.append(0x20);
    cmd.append(0x53);
    cmd.append(0x54);
    cmd.append(0x6C);
    cmd.append(0x6D);
    cmd.append(0x73);
    cmd.append(0x03);

    return cmd;
}

QByteArray Command::start()
{
    QByteArray cmd;
    // HEX: 02 73 4D 4E 20 52 75 6E 03
    cmd.append(0x02);
    cmd.append(0x73);
    cmd.append(0x4D);
    cmd.append(0x4E);
    cmd.append(0x20);
    cmd.append(0x52);
    cmd.append(0x75);
    cmd.append(0x6E);
    cmd.append(0x03);

    return cmd;
}

QByteArray Command::trig()
{
    QByteArray cmd;
    //  HEX: 02 73 52 4E 20 4C 4D 44 73 63 61 6E 64 61 74 61 03
    cmd.append(0x02);
    cmd.append(0x73);
    cmd.append(0x52);
    cmd.append(0x4E);
    cmd.append(0x20);
    cmd.append(0x4C);
    cmd.append(0x4D);
    cmd.append(0x44);
    cmd.append(0x73);
    cmd.append(0x63);
    cmd.append(0x61);
    cmd.append(0x6E);
    cmd.append(0x64);
    cmd.append(0x61);
    cmd.append(0x74);
    cmd.append(0x61);
    cmd.append(0x03);

    return cmd;
}

QByteArray Command::autoTrig()
{
    //    连续测量：发送指令后，LMS 会实时返回其测量数据
    //    指令 HEX: 02 73 45 4E 20 4C 4D 44 73 63 61 6E 64 61 74 61 20 31 03
    QByteArray cmd;

    cmd.append(0x02);
    cmd.append(0x73);
    cmd.append(0x45);
    cmd.append(0x4E);
    cmd.append(0x20);
    cmd.append(0x4C);
    cmd.append(0x4D);
    cmd.append(0x44);
    cmd.append(0x73);
    cmd.append(0x63);
    cmd.append(0x61);
    cmd.append(0x6E);
    cmd.append(0x64);
    cmd.append(0x61);
    cmd.append(0x74);
    cmd.append(0x61);
    cmd.append(0x20);
    cmd.append(0x31);
    cmd.append(0x03);

    return cmd;
}

QByteArray Command::stopTrig()
{
    // 连续测量停止：发送指令后，LMS 停止向外发送测量数据
    // 指令 HEX: 02 73 45 4E 20 4C 4D 44 73 63 61 6E 64 61 74 61 20 30 03
    QByteArray cmd;

    cmd.append(0x02);
    cmd.append(0x73);
    cmd.append(0x45);
    cmd.append(0x4E);
    cmd.append(0x20);
    cmd.append(0x4C);
    cmd.append(0x4D);
    cmd.append(0x44);
    cmd.append(0x73);
    cmd.append(0x63);
    cmd.append(0x61);
    cmd.append(0x6E);
    cmd.append(0x64);
    cmd.append(0x61);
    cmd.append(0x74);
    cmd.append(0x61);
    cmd.append(0x20);
    cmd.append(0x30);
    cmd.append(0x03);

    return cmd;
}
