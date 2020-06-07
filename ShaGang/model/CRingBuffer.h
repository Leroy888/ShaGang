#ifndef CRINGBUFFER_H
#define CRINGBUFFER_H

#include <mutex>
#include <assert.h>
#include "com/Global.h"
#include "com/Common.h"
#include <QThread>

#include <QDebug>

class CPoints3DRingBuffer
{
public:
    CPoints3DRingBuffer(unsigned int size)
    {
        m_nSize = size;
        m_pBuffer = new Points3D[m_nSize];

        if (m_pBuffer != NULL)
        {                
            m_nUnreadSize = 0;
            m_nWritePos = 0;
            m_nReadPos = 0;
        }
    }

    ~CPoints3DRingBuffer()
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (m_pBuffer != NULL)
        {
            delete[] m_pBuffer;
            m_pBuffer = NULL;
            m_nSize = 0;
            m_nUnreadSize = 0;
            m_nWritePos = 0;
            m_nReadPos = 0;
        }
    }

    //清空环形缓冲区
    void clear()
    {
        std::lock_guard<std::mutex> lock(mtx);
        m_nUnreadSize = 0;
        m_nWritePos = 0;
        m_nReadPos = 0;
    }

//    //设置环形缓冲区
//    //nSize：缓冲区大小
//    void resetBufferSize(unsigned int nSize)
//    {
//        std::lock_guard<std::mutex> lock(mtx);
//        if (m_pBuffer != NULL)
//        {
//            delete[] m_pBuffer;
//            m_pBuffer = NULL;
//            m_nSize = 0;
//            m_nUnreadSize = 0;
//            m_nWritePos = 0;
//            m_nReadPos = 0;
//        }

//        m_pBuffer = new T[nSize];
//        if (m_pBuffer != NULL)
//        {
//            memset(m_pBuffer, 0x00, nSize * sizeof(T));
//            m_nSize = nSize;
//            m_nUnreadSize = 0;
//            m_nWritePos = 0;
//            m_nReadPos = 0;
//        }
//    }

    unsigned int getSegmentSize()
    {
        return m_nSize;
    }

    unsigned int getSegmentPointsSize()
    {
        return PLOUGH_3D_SEGMENT_POINTS_MAX;
    }

    unsigned int getLength()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return m_nUnreadSize;
    }

    //写入数据到环形缓冲区
    //返回值：写入的数据大小
    void beginWritePointData(int segmentIndex) {
        // 判断当前截面的index是否超过size。
        if(segmentIndex>=PLOUGH_3D_SEGMENT_MAX) {
            return;
        }

        m_pBuffer[segmentIndex].enabled = false;
    }

    //写入数据到环形缓冲区
    //返回值：写入的数据大小
    void endWritePointData(int segmentIndex) {
        // 判断当前截面的index是否超过size。
        if(segmentIndex>=PLOUGH_3D_SEGMENT_MAX) {
            return;
        }

        m_pBuffer[segmentIndex].enabled = true;
    }

    void Enable(int segmentIndex, bool enabled) {
        if(segmentIndex>= m_nSize) {
            return;
        }

        m_pBuffer[segmentIndex].enabled = enabled;
    }

    // 写截面的点数据
    unsigned int writePointData(int segmentIndex, int pointIndex, double x, double y, double z )
    {
        //if (nSize > m_nSize - m_nUnreadSize)//缓冲区大小不足时，仅写入最前面的数据
        //    nSize = m_nSize - m_nUnreadSize;

        // 判断当前截面的index是否超过size。
        if(segmentIndex>= m_nSize || pointIndex>=PLOUGH_3D_SEGMENT_POINTS_MAX) {
            return 0;
        }

        if(m_pBuffer[segmentIndex].points) {
            m_pBuffer[segmentIndex].points[pointIndex].x = x;
            m_pBuffer[segmentIndex].points[pointIndex].y = y;
            m_pBuffer[segmentIndex].points[pointIndex].z = z;
        }


//        m_nWritePos += nSize;
//        if (m_nWritePos >= m_nSize)
//            m_nWritePos %= m_nSize;


        return pointIndex + 1;
    }

    // 读取截面数据
    Points3D* readSegmentData(int segmentIndex) {
        // 判断当前截面的index是否超过size。
        if(segmentIndex>=m_nSize ) {
            return NULL;
        }

        return &m_pBuffer[segmentIndex];
    }

    // 读取截面点数据
    Point* readSegmentPointData(int segmentIndex, int pointIndex) {
        // 判断当前截面的index是否超过size。
        if(segmentIndex>=m_nSize || pointIndex>=PLOUGH_3D_SEGMENT_POINTS_MAX) {
            return NULL;
        }

        return &m_pBuffer[segmentIndex].points[pointIndex];
    }

private:

    //写入数据到环形缓冲区
    //返回值：写入的数据大小
    unsigned int writeData(const Points3D* pT, unsigned int nSize = 1)
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (nSize > m_nSize - m_nUnreadSize)//缓冲区大小不足时，仅写入最前面的数据
            nSize = m_nSize - m_nUnreadSize;

        if (nSize > 0)
        {
            if (m_nWritePos + nSize <= m_nSize)
            {
                memcpy(&m_pBuffer[m_nWritePos], pT, nSize * sizeof(Points3D));
                qDebug()<<"Buffer ID"<<m_pBuffer<<__FUNCTION__<<"writePos ="<<m_nWritePos;
            }
            else
            {
                memcpy(&m_pBuffer[m_nWritePos], pT, (m_nSize - m_nWritePos) * sizeof(Points3D));
                if (nSize - (m_nSize - m_nWritePos) > 0)
                    memcpy(m_pBuffer, &pT[m_nSize - m_nWritePos], (nSize - (m_nSize - m_nWritePos)) * sizeof(Points3D));
            }

        //    m_nUnreadSize += nSize;
            m_nWritePos += nSize;
            if (m_nWritePos >= m_nSize)
                m_nWritePos %= m_nSize;
        }

        return nSize;
    }
    //从环形缓冲区读取数据
    //nSize：缓冲区大小
    //返回值：读取的数据大小
    unsigned int readData(Points3D* pT, unsigned int nSize = 1)
    {
        std::lock_guard<std::mutex> lock(mtx);
        m_nUnreadSize = m_nSize;
        m_nReadPos = 0;
        if (nSize > m_nUnreadSize || m_nUnreadSize == 0)
            nSize = m_nUnreadSize;

        if (nSize > 0)
        {
            if (m_nReadPos + nSize <= m_nSize)
            {
                memcpy(pT, &m_pBuffer[m_nReadPos], nSize * sizeof(Points3D));
                qDebug()<<"Buffer ID"<<m_pBuffer<<"readPos ="<<m_nReadPos<<"nSize ="<<nSize;
//                for (int i = 0; i < 395; ++i) {
//                    qDebug()<<"enabled ="<<pT->enabled<<" x ="<<pT->points[i].x<<" y ="<<pT->points[i].y<<" z ="<<pT->points[i].z;
//                }
            }
            else
            {
                memcpy(pT, &m_pBuffer[m_nReadPos], (m_nSize - m_nReadPos) * sizeof(Points3D));
                if (nSize - (m_nSize - m_nReadPos) > 0)
                    memcpy(&pT[m_nSize - m_nReadPos], m_pBuffer, (nSize - (m_nSize - m_nReadPos)) * sizeof(Points3D));
                qDebug()<<"nSize > unReadSize";
            }

         //   m_nUnreadSize -= nSize;
          //  m_nReadPos += nSize;
//            if (m_nReadPos >= m_nSize)
//                m_nReadPos %= m_nSize;
            m_nReadPos = 0;
            m_nUnreadSize = 0;
        }

        return nSize;
    }
private:
    Points3D* m_pBuffer;			//缓冲区
    unsigned int m_nSize;			//缓冲区大小

    unsigned int m_nUnreadSize;		//未读取的数据大小

    unsigned int m_nWritePos;		//写入下标
    unsigned int m_nReadPos;		//读取下标

    std::mutex mtx;//线程锁
};

#endif // CRINGBUFFER_H
