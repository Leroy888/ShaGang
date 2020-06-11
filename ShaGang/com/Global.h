#ifndef GLOBAL_H
#define GLOBAL_H

#include "model/CRingBuffer.h"
#include "com/Common.h"


class Global
{
public:
    Global(){}
    ~Global(){}

    static void destroy()
    {
        if(m_ringBuffer)
            delete m_ringBuffer;
    }

    static CPoints3DRingBuffer* m_ringBuffer;

private:

};



class GblRingBuffer
{
public:
    static void setDevices(const QStringList &devList);

    static GblRingBuffer* getInstance();

    QMap<QString,CPoints3DRingBuffer*> getRingBuffers();

    CPoints3DRingBuffer *getRingBuffer(const QString &device);
    int getXpos(const QString &device) const;
    int setXpos(const QString &device, const int xPos);
private:
    GblRingBuffer();

    static GblRingBuffer* m_glbRingBuffers;
    QMap<QString,CPoints3DRingBuffer*> m_ringBuffers;
    QMap<QString,int> m_xPosMap;
    static QStringList m_devList;
};



#endif // GLOBAL_H
