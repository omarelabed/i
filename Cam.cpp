#include "Cam.h"

Cam::Cam()
{
    capture = cvCaptureFromCAM(0);
    relX_0 = 0.0; relY_0 = 0.0;
    relX_1 = 0.0; relY_1 = 0.0;
}

Cam::~Cam()
{
    // self-destruct
    cvReleaseCapture(&capture);
}

void Cam::init(){
    // GREEN
    _h0 = 40; _s0 = 100; _v0 = 100;
    h0 = 65; s0 = 255; v0 = 255;
    // BLUE
//    _h1 = 94; _s1 = 90; _v1 = 90;
//    h1 = 130; s1 = 255; v1 = 255;
    _h1 = 113; _s1 = 204; _v1 = 204;
    h1 = 123; s1 = 255; v1 = 255;
    updateColorPositions();
}

void Cam::updateColorPosition(IplImage* frame, int i){
    IplImage* imgHSV = cvCreateImage(cvGetSize(frame), 8, 3);
    cvCvtColor(frame, imgHSV, CV_BGR2HSV);
    IplImage* imgThreshed = cvCreateImage(cvGetSize(frame), 8, 1);
    // filter out color in range
    if (i==1)
        cvInRangeS(imgHSV, cvScalar(_h1, _s1, _v1), cvScalar(h1, s1, v1), imgThreshed);
    else
        cvInRangeS(imgHSV, cvScalar(_h0, _s0, _v0), cvScalar(h0, s0, v0), imgThreshed);

    // we don't need the imgHSV anymore, so we release it
    cvReleaseImage(&imgHSV);

    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgThreshed, moments, 1);

    // the actual moment values
    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);
    double area = cvGetSpatialMoment(moments, 0, 0);

    static int posX = 0;
    static int posY = 0;

    posX = moment10/area;
    posY = moment01/area;

    cv::Size frameSize = cvGetSize(frame);
    if (i==1){
        relX_1 = (double)posX/(double)frameSize.width;
        relY_1 = (double)posY/(double)frameSize.height;
    }
    else{
        relX_0 = (double)posX/(double)frameSize.width;
        relY_0 = (double)posY/(double)frameSize.height;
    }
    cvReleaseImage(&imgThreshed);

    delete moments;
}

void Cam::updateColorPositions(){

    if (!capture)
    {
        printf("No capture.\n");
    }

    // This one is going to hold each frame coming from the cam
    IplImage* frame = 0;
    frame = cvQueryFrame(capture);
    if (!frame) printf("No frame grabbed.\n");

    updateColorPosition(frame, 0);
    updateColorPosition(frame, 1);
}
