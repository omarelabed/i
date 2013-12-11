//
// Upon first time for generating VC 2008 project file
//
// $QTDIR$\bin\qmake -tp vc
//

/****************************************************************************
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QApplication>
#include "GLRender.h"
#include "CamCapturer.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cvaux.hpp>

//! [0]
int main(int argc, char *argv[])
{
//    // Initialize capturing live feed from the camera
//    CvCapture* capture = 0;
//    capture = cvCaptureFromCAM(0);

    // Couldn't get a device? Throw an error and quit
//    if(!capture)
//    {
//        printf("Could not initialize capturing...\n");
//        return -1;
//    }

//    // The two windows we'll be using
//    cvNamedWindow("video");
//    cvNamedWindow("thresh");

//    // This image holds the "scribble" data...
//    // the tracked positions of the ball
//    IplImage* imgScribble = NULL;

//    // An infinite loop
//    while(true)
//    {
//        // Will hold a frame captured from the camera
//        IplImage* frame = 0;
//        frame = cvQueryFrame(capture);

//        // If we couldn't grab a frame... quit
//        if(!frame)
//            break;

//        // If this is the first frame, we need to initialize it
//        if(imgScribble == NULL)
//        {
//            imgScribble = cvCreateImage(cvGetSize(frame), 8, 3);
//        }

//        cv::Size frameSize = cvGetSize(frame);

//        // Holds the yellow thresholded image (yellow = white, rest = black)
//        IplImage* imgYellowThresh = GetThresholdedImage(frame);

//        // Calculate the moments to estimate the position of the ball
//        CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
//        cvMoments(imgYellowThresh, moments, 1);

//        // The actual moment values
//        double moment10 = cvGetSpatialMoment(moments, 1, 0);
//        double moment01 = cvGetSpatialMoment(moments, 0, 1);
//        double area = cvGetCentralMoment(moments, 0, 0);

//        // Holding the last and current ball positions
//        static int posX = 0;
//        static int posY = 0;

//        int lastX = posX;
//        int lastY = posY;

//        posX = moment10/area;
//        posY = moment01/area;

//        double relX = (double)posX/(double)frameSize.width;
//        double relY = (double)posY/(double)frameSize.height;

//        // Print it out for debugging purposes
//        printf("position (%d,%d)", posX, posY);
//        printf(" -- relative posn: (%f,%f)\n", relX, relY);

//        // We want to draw a line only if its a valid position
//        if(lastX>0 && lastY>0 && posX>0 && posY>0)
//        {
//            // Draw a yellow line from the previous point to the current point
//            cvLine(imgScribble, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255), 5);
//        }

//        // Add the scribbling image and the frame... and we get a combination of the two
//        cvAdd(frame, imgScribble, frame);
//        cvShowImage("thresh", imgYellowThresh);
//        cvShowImage("video", frame);

//        // Wait for a keypress
//        int c = cvWaitKey(10);
//        if(c!=-1)
//        {
//            // If pressed, break out of the loop
//            break;
//        }

//        // Release the thresholded image... we need no memory leaks.. please
//        cvReleaseImage(&imgYellowThresh);

//        delete moments;
//    }

//    // We're done using the camera. Other applications can now use it
//    cvReleaseCapture(&capture);

//    CamCapturer camCapturer();

    QApplication app(argc, argv);
    GLRender viewer( 0, Qt::Window );

    app.setActiveWindow( &viewer );
    viewer.show();
    return app.exec();
}
//! [0]
