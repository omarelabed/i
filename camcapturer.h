#ifndef CAMCAPTURER_H
#define CAMCAPTURER_H

#include <opencv2/opencv.hpp>

class CamCapturer
{
public:
    CamCapturer();
    virtual ~CamCapturer();
    IplImage* getThresholdedImage(IplImage* img);
    float *getCoordinates();

private:
    CvCapture* capture;
    // This image holds the "scribble" data...
    IplImage* imgScribble;
    // Holds the light thresholded image (yellow = white, rest = black)
    IplImage* imgLightThresh;
    CvMoments *moments;
};

#endif // CAMCAPTURER_H
