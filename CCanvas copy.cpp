#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"

using namespace std;

//-----------------------------------------------------------------------------

void CCanvas::initializeGL()
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			          // Black Background
  glClearDepth(1.0f);									                // Depth Buffer Setup
  glEnable(GL_DEPTH_TEST);							              // Enables Depth Testing
  glDepthFunc(GL_LEQUAL);								              // The Type Of Depth Testing To Do
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
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

    // So we have to compute the coordinate system of the camera
    // origin = camera position = view point = VP
    Point3d VP (eyex, eyey, eyez);
    // (negative) viewing direction = view plane normal = VPN
    Point3d c (centerx, centery, centerz);
    Point3d VPN = VP-c;
    // ceiling (or sky) direction = view up vector = VUP
    Point3d VUP(upx, upy, upz);
    // cout<<"VUP: "<<VUP<<endl;
    // we then compute x', y' and z' (see slides)
    Point3d z = VPN.normalized();
    Point3d x = ((VUP.normalized())^z);
    Point3d y = z^x;

    mat[0]=x.x();
    mat[1]=x.y();
    mat[2]=x.z();
    mat[3]=0.0;

    mat[4]=y.x();
    mat[5]=y.y();
    mat[6]=y.z();
    mat[7]=0.0;

    mat[8]=z.x();
    mat[9]=z.y();
    mat[10]=z.z();
    mat[11]=0.0;

    mat[12]=VP.x();
    mat[13]=VP.y();
    mat[14]=VP.z();
    mat[15]=1.0;
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

void CCanvas::paintGL()
{
  // clear screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // set model-view matrix
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  lookAt( 0,0,0,  0,0,-1,  0,1,0 );     // camera position , "look at" point , view-up vector

  // set up a sphere
  Sphere sphere (20,10);

  // transform and draw sphere
  glTranslated (0.5, 0.5, -5.0);
    glScaled (2.0, 2.0, 2.0);
    glRotated ( tau, 1,0,0 );

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  sphere.draw();

  tau += 1.0;
}
