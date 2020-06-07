#ifndef GLOBAL_H
#define GLOBAL_H

#include "model/CRingBuffer.h"
#include <QDebug>
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

CPoints3DRingBuffer* Global::m_ringBuffer = new CPoints3DRingBuffer (PLOUGH_3D_SEGMENT_MAX);

#endif // GLOBAL_H
