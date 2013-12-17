#ifndef CAM_H
#define CAM_H

#include <opencv2/opencv.hpp>

class Cam
{
public:
    Cam();
    virtual ~Cam();
    double relX_0; double relY_0;
    double relX_1; double relY_1;
    // color 0
    int _h0; int _s0; int _v0;
    int h0; int s0; int v0;
    // color 1
    int _h1; int _s1; int _v1;
    int h1; int s1; int v1;
    void init();
    void updateColorPosition(IplImage* frame, int i);
    void updateColorPositions();
private:
    CvCapture* capture;
};

#endif // CAM_H
