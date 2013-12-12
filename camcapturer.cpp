#include "CamCapturer.h"
//#include <opencv/cvaux.h>
#include <opencv2/opencv.hpp>

// Constructor
CamCapturer::CamCapturer(){
    // Initialize capturing live feed from the camera
    capture = cvCaptureFromCAM(0);
    imgScribble = NULL;
    cvNamedWindow("video");
    cvNamedWindow("thresh");
}

CamCapturer::~CamCapturer(){
    // We're done using the camera. Other applications can now use it
    cvReleaseCapture(&capture);
    // Release the thresholded image... we need no memory leaks.. please
    cvReleaseImage(&imgLightThresh);

    delete moments;
}

IplImage* CamCapturer::getThresholdedImage(IplImage* img)
{
    // Convert the image into an HSV image
    IplImage* imgHSV = cvCreateImage(cvGetSize(img), 8, 3);
    cvCvtColor(img, imgHSV, CV_BGR2HSV);
//    cvCvtColor(img, imgHSV, CV_BGR2RGB);

    IplImage* imgThreshed = cvCreateImage(cvGetSize(img), 8, 1);

    cvInRangeS(imgHSV, cvScalar(40, 100, 100), cvScalar(65, 255, 255), imgThreshed);

    cvReleaseImage(&imgHSV);

    return imgThreshed;
}


float *CamCapturer::getCoordinates(){
    if(!capture)
    {
        printf("Could not initialize capturing...\n");
        float xy[]={0.0, 0.0};
        return xy;
    }

    // Will hold a frame captured from the camera
    IplImage* frame = 0;
    frame = cvQueryFrame(capture);

    // If we couldn't grab a frame... quit
    if(!frame) printf("Couldn't grab a frame...\n");

    // If this is the first frame, we need to initialize it
    if(imgScribble == NULL)
    {
        imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
    }

    cv::Size frameSize = cvGetSize(frame);

    // Holds the yellow thresholded image (yellow = white, rest = black)
    imgLightThresh = getThresholdedImage(frame);

    // Calculate the moments to estimate the position of the light
    moments = (CvMoments*)malloc(sizeof(CvMoments));
    cvMoments(imgLightThresh, moments, 1);

    // The actual moment values
    double moment10 = cvGetSpatialMoment(moments, 1, 0);
    double moment01 = cvGetSpatialMoment(moments, 0, 1);
    double area = cvGetCentralMoment(moments, 0, 0);

    // Holding the last and current ball positions
    static int posX = 0;
    static int posY = 0;

    int lastX = posX;
    int lastY = posY;

    posX = moment10/area;
    posY = moment01/area;

    double relX = (double)posX/(double)frameSize.width;
    double relY = (double)posY/(double)frameSize.height;

    // Print it out for debugging purposes
//    printf("position (%d,%d)", posX, posY);
//    printf(" -- relative posn: (%f,%f)\n", relX, relY);

    // We want to draw a line only if its a valid position
    if(lastX>0 && lastY>0 && posX>0 && posY>0)
    {
        // Draw a yellow line from the previous point to the current point
        cvLine(imgScribble, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255), 5);
    }

    // Add the scribbling image and the frame... and we get a combination of the two
    cvAdd(frame, imgScribble, frame);
    cvShowImage("thresh", imgLightThresh);
    cvShowImage("video", frame);

    float xy[] = {relX, relY};
    return xy;
}
