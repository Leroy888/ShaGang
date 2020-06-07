#ifndef COMMON_H
#define COMMON_H

#include <QString>

#define PLOUGH_3D_SEGMENT_MAX 10000
#define PLOUGH_3D_SEGMENT_POINTS_MAX 361


struct Point
{
    double x = 0;
    double y = 0;
    double z = 0;
};

class Points3D
{
public:
    Points3D(){
        enabled = false;
        points = new Point[PLOUGH_3D_SEGMENT_POINTS_MAX];
    }
    ~Points3D()
    {
        delete[] points;
    }

    bool enabled;
    Point* points;
};

enum SmsArea{
    vArea = 0x84,
    mArea = 0x83,
    oArea = 0x82,
    iArea = 0x81,
    cArea = 0x1c,
    tArea = 0x1d
};

class Common
{
public:
    Common();
};

#endif // COMMON_H
