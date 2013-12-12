#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"
#include "CamCapturer.h"
#include <math.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

using namespace std;

//-----------------------------------------------------------------------------

void convertLightCoords(int x, int y){
    //    lightX = (double)x;
    //    lightY = (double)y;
    cout<<"mouse posn ("<<x<<","<<y<<")"<<endl;
}
//glut:glutPassiveMotionFunc(setLightCoords);


void CCanvas::initializeGL()
{
    printf("initializeGL\n");
   // cout<<"xy "<<camCapturer.getCoordinates()<<endl;
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);   // Background color
    glClearDepth(1.0f);                     // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                 // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Really Nice Perspective Calculations
    glEnable( GL_NORMALIZE );
    glEnable( GL_RESCALE_NORMAL );

    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat position[] = {0.0, 0.0, 1.0, 1.0};

    glShadeModel( GL_SMOOTH );

    glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    glLightfv( GL_LIGHT0, GL_POSITION, position );

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

};

//-----------------------------------------------------------------------------


void  CCanvas::glPerspective(
        const GLdouble fovy,
        const GLdouble aspect,
        const GLdouble zNear,
        const GLdouble zFar)
{
    const GLdouble d=1.0/tan(fovy/360.0*PI);
    const GLdouble delta=zNear-zFar;

    GLdouble *mat=new GLdouble[16];

    mat[0]=d/aspect;
    mat[1]=0;
    mat[2]=0;
    mat[3]=0;

    mat[4]=0;
    mat[5]=d;
    mat[6]=0;
    mat[7]=0;

    mat[8]=0;
    mat[9]=0;
    mat[10]=(zNear+zFar)/delta;
    mat[11]=-1;

    mat[12]=0;
    mat[13]=0;
    mat[14]=2*zNear*zFar/delta;
    mat[15]=0;


    glMultMatrixd(mat);

    delete[] mat;
}


void CCanvas::  lookAt(const GLdouble eyex,
                       const GLdouble eyey,
                       const GLdouble eyez,
                       const GLdouble centerx,
                       const GLdouble centery,
                       const GLdouble centerz,
                       const GLdouble upx,
                       const GLdouble upy,
                       const GLdouble upz)
{


    GLdouble *mat=new GLdouble[16];

    // The vector from the eye to the center point normalized
    Point3d VPN = Point3d(centerx-eyex, centery-eyey, centerz-eyez);
    VPN.normalize();

    // Computing vectors a and b (side and forward)
    Point3d up = Point3d(upx, upy, upz);
    up.normalize();
    Point3d a = VPN ^ up;
    a.normalize();

    Point3d b = a ^ VPN;
    b.normalize();

    // Building the matrix
    mat[0] = a.x();
    mat[1] = a.y();
    mat[2] = a.z();
    mat[3] = 0;
    mat[4] = b.x();
    mat[5] = b.y();
    mat[6] = b.z();
    mat[7] = 0;
    mat[8] = -VPN.x();
    mat[9] = -VPN.y();
    mat[10] = -VPN.z();
    mat[11] = 0;
    mat[12] = 0;
    mat[13] = 0;
    mat[14] = 0;
    mat[15] = 1;


    glMultMatrixd(mat);

    delete[] mat;


}

void CCanvas::resizeGL(int width, int height)
{
    // set up the window-to-viewport transformation
    glViewport( 0,0, width,height );

    // vertical camera opening angle
    double beta = 90.0;

    // aspect ratio
    double gamma;
    if (height > 0)
        gamma = width/(double)height;
    else
        gamma = width;

    // front and back clipping plane at
    double n = -1.0;
    double f = -10.0;

    // frustum corners
    double t = -tan(beta*3.14159/360.0) * n;
    double b = -t;
    double r = gamma * t;
    double l = -r;

    // set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( l,r , b,t , -n,-f );

    // alternatively, directly from alpha and gamma
    //  glPerspective( beta, gamma, -n, -f );
}

//-----------------------------------------------------------------------------

bool increasing = true;
double pace = 3.0;
double irisTau = 0.22;
int lastxAng=0;
int lastyAng=0;
void CCanvas::paintGL()
{
    GLfloat relX = camCapturer.getCoordinates()[0];
    GLfloat relY = camCapturer.getCoordinates()[1];
    //cout<<"("<<relX<<","<<relY<<")"<<endl;

    //    GLfloat ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    //    GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    //    GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
    //    GLfloat newposition[] = {0.0, 0.0, 0.0, 1.0};

    //    glShadeModel( GL_SMOOTH );

    //    glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
    //    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    //    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    //    glLightfv( GL_LIGHT0, GL_POSITION, newPosition );


    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    lookAt( 0,0,0,  0,0,-1,  0,1,0 );     // camera position , "look at" point , view-up vector

    // set up a sphere
    Sphere sphere1 (80,40);
   // Sphere sphere2 (80,40);
    //Sphere sphere3 (80,40);

    GLfloat mat_emission[] = {0.0, 0.0, 0.0, 0.0};
    GLfloat mat_ambient[] = { 0.20, 0.20, 0.20, 1.0 };
    GLfloat mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_specular[] = { 0.6,0.6, 0.6, 1.0 };
    GLfloat shininess = 51.0;

    glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf ( GL_FRONT, GL_SHININESS, shininess );

    // transform and draw sphere
    glTranslated (0.0, 0.0, -5.0);
    glScaled (2.0, 2.0, 2.0);
   // glRotated ( 90, 0,1,0 );
    bool seesStuff = false;


    if (relX>=0 && relY>=0){
        seesStuff = true;
        Point2d lookAtPoint = Point2d(800.0*relX, 600.0*relY);
        float xAng = atan((400.0-lookAtPoint.x())/1200.0);
        float yAng = atan((300.0-lookAtPoint.y())/900.0);
        xAng = xAng*180.0/PI;
        yAng = yAng*180.0/PI;
        //cout<<"xAng="<<xAng<<endl;
        //cout<<"yAng="<<yAng<<endl;
        glRotated ( xAng+90, 0,1,0 );
        glRotated ( -yAng-10.0, 0,0,1 );
        lastxAng=xAng;
        lastyAng=yAng;
    }else{

        if(lastxAng>1){
        lastxAng-=3;}
        else if(lastxAng<-1){
        lastxAng+=3;
        }
        else{
        lastxAng=0;
        }
        if(lastyAng>-9){
        lastyAng-=3;}
        else if(lastyAng<-11){
        lastyAng+=3;}
        else{
        lastyAng=-10;
        }

        glRotated ( lastxAng+90, 0,1,0 );
        glRotated (-lastyAng-10.0, 0,0,1 );
    }

    //    glRotated ( tau, 0,1,0 );

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    sphere1.draw();

//    Point2d c = Point2d(80, 80);

//    GLfloat mat_emission2[] = {0.0, 0.0, 0.0, 0.0};
//    GLfloat mat_ambient2[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse2[] = { 0.0, 0.0, 0.5, 1.0 };
//    GLfloat mat_specular2[] = { 0.2,0.2, 0.6, 1.0 };
//    GLfloat shininess2 = 80.0;

//    glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission2 );
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient2 );
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse2 );
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular2 );
//    glMaterialf ( GL_FRONT, GL_SHININESS, shininess2 );

//    // transform and draw sphere
//    // glRotated ( tau, 0,1,0 );
//    glTranslated (0.0, 0.0, 0.85);
//    glScaled (0.44, 0.44, 0.2);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //sphere2.draw();

//    GLfloat mat_emission3[] = {0.0, 0.0, 0.0, 0.0};
//    GLfloat mat_ambient3[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_diffuse3[] = { 0.0, 0.0, 0.0, 1.0 };
//    GLfloat mat_specular3[] = { 0.2,0.2, 0.2, 1.0 };
//    GLfloat shininess3 = 80.0;

//    glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission3 );
//    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient3 );
//    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse3 );
//    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular3 );
//    glMaterialf ( GL_FRONT, GL_SHININESS, shininess3 );

    // transform and draw sphere
    // glRotated ( tau, 0,1,0 );
//    glTranslated (0.0, 0.0, 0.96);
//    double iris;

//    if (seesStuff){
//        iris = 0.33;
//    } else {
//        iris = 0.22;
//    }
    //    if (iris < 0.11) iris=0.11;
  //  glScaled (iris, iris, 0.1);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  //  sphere3.draw();

    if (increasing && tau==90){
        increasing = false;
        tau-=pace;
    } else if (!increasing && tau==-90){
        increasing = true;
        tau += pace;
    } else if (increasing){
        tau+=pace;
    } else if (!increasing){
        tau-=pace;
    }
}
