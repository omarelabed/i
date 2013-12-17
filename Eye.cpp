#include "Eye.h"
#include "Base.h"
#include <math.h>

*Eye::Eye(const int &lats, const int &longs)
    :lats(lats), longs(longs)
{
    QImage img;
    glEnable(GL_TEXTURE_2D);
    if (!img.load(QString("../../../../i/Eyes/circ1.jpg"))){
              qWarning("image not loaded");
            }

    img=QGLWidget::convertToGLFormat(img);
    glGenTextures(1, &name);
    glBindTexture(GL_TEXTURE_2D, name);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, img.width(), img.height(),0,GL_RGBA, GL_UNSIGNED_BYTE,img.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,name);
    build();


}




void Eye::build()
{
    float step=2*PI/lats;

    for(int i=0;i<lats;++i)
        buildSegment(i,step);
}

void Eye::changeTexture(int light){
    glEnable(GL_TEXTURE_2D);
    QImage img;
    switch(light){
    case(15):
        img.load(QString("../../../../i/Eyes/circ16.jpg"));
        break;
    case(14):
        img.load(QString("../../../../i/Eyes/circ15.jpg"));
         break;
    case(13):
        img.load(QString("../../../../i/Eyes/circ14.jpg"));
         break;
    case(12):
        img.load(QString("../../../../i/Eyes/circ13.jpg"));
         break;
    case(11):
        img.load(QString("../../../../i/Eyes/circ12.jpg"));
         break;
    case(10):
        img.load(QString("../../../../i/Eyes/circ11.jpg"));
         break;
    case(9):
        img.load(QString("../../../../i/Eyes/circ10.jpg"));
         break;
    case(8):
        img.load(QString("../../../../i/Eyes/circ9.jpg"));
        break;
    case(7):
        img.load(QString("../../../../i/Eyes/circ8.jpg"));
        break;
    case(6):
        img.load(QString("../../../../i/Eyes/circ7.jpg"));
        break;
    case(5):
        img.load(QString("../../../../i/Eyes/circ6.jpg"));
        break;
    case(4):
        img.load(QString("../../../../i/Eyes/circ5.jpg"));
        break;
    case(3):
        img.load(QString("../../../../i/Eyes/circ4.jpg"));
        break;
    case(2):
        img.load(QString("../../../../i/Eyes/circ3.jpg"));
        break;
    case(1):
        img.load(QString("../../../../i/Eyes/circ2.jpg"));
        break;
    case(0):
        img.load(QString("../../../../i/Eyes/circ1.jpg"));
        break;
    }
    img=QGLWidget::convertToGLFormat(img);
    glGenTextures(1, &name);
    glBindTexture(GL_TEXTURE_2D, name);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, img.width(), img.height(),0,GL_RGBA, GL_UNSIGNED_BYTE,img.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,name);
}

void Eye::buildSegment(const int &index, const float &phiStep)
{
    float phis[]={index*phiStep,(index+1)*phiStep};

    strips.push_back(PointArray());
    textures.push_back(TextureArray());

    PointArray &segment = strips.back();
    TextureArray &txt = textures.back();

    set(Point3d(0,0,1),Point2d(0,1.0f*index/lats),segment,txt);

    float step=PI/longs;
    for(int i=1;i<longs;++i)
    {
        const float theta=i*step;

        for(int j=0;j<2;++j)
        {
            const float phi=phis[j];
            const Point3d p(
                        sin(theta)*cos(phi),
                        sin(theta)*sin(phi),
                        cos(theta));

            set(p,Point2d(1.0f*i/longs,1.0f*(index+j)/lats),segment,txt);
        }
    }

    set(Point3d(0,0,-1),Point2d(1,1.0f*index/lats),segment,txt);
}

void Eye::set(const Point3d &p, const Point2d &t, PointArray &segment, TextureArray &txt) const
{
    segment.push_back(p);
    assert(t.x()>=0 && t.x()<=1);
    //assert(t.y()>=0 && t.y()<=1);

    txt.push_back(t);
}

void Eye::draw()
{
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


    for(unsigned int i=0;i<strips.size();++i)
    {
        const PointArray &segment=strips[i];
        const TextureArray &txt=textures[i];


        glBegin(GL_TRIANGLE_STRIP);
        for(unsigned int j=0;j<segment.size();++j)
        {
            const Point3d &p=segment[j];
            const Point2d &t=txt[j];

            glNormal3d(p.x(),p.y(),p.z());
            glTexCoord2d(t.x(),t.y());
            glVertex3d(p.x(),p.y(),p.z());
        }
        glEnd();
    }
}
