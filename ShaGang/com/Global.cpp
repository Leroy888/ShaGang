#include "Global.h"

#include <QDebug>

CPoints3DRingBuffer* Global::m_ringBuffer = new CPoints3DRingBuffer (PLOUGH_3D_SEGMENT_MAX);
GblRingBuffer* GblRingBuffer::m_glbRingBuffers = nullptr;
QStringList GblRingBuffer::m_devList ;


GblRingBuffer::GblRingBuffer()
{
    for (auto dev : m_devList) {
        CPoints3DRingBuffer* ringBuffer = new CPoints3DRingBuffer(PLOUGH_3D_SEGMENT_MAX);
        m_ringBuffers.insert(dev, ringBuffer);
        m_xPosMap.insert(dev, 0);
        qDebug()<<__FUNCTION__<<"Dev"<<dev;
    }
    qDebug()<<__FUNCTION__;
}

void GblRingBuffer::setDevices(const QStringList &devList)
{
    m_devList = devList;
    qDebug()<<__FUNCTION__;
}

GblRingBuffer *GblRingBuffer::getInstance()
{
    if(m_glbRingBuffers == nullptr)
    {
        m_glbRingBuffers = new GblRingBuffer;
    }

    return m_glbRingBuffers;
}

QMap<QString, CPoints3DRingBuffer *> GblRingBuffer::getRingBuffers()
{
    return m_ringBuffers;
}

CPoints3DRingBuffer* GblRingBuffer::getRingBuffer(const QString& device)
{
    return m_ringBuffers.value(device);
}

int GblRingBuffer::getXpos(const QString &device) const
{
    return m_xPosMap.value(device);
}

int GblRingBuffer::setXpos(const QString &device, const int xPos)
{
    m_xPosMap.insert(device, xPos);
}


