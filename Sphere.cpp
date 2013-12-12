#include "Sphere.h"
#include "Base.h"
#include <math.h>

Sphere::Sphere(const int &lats, const int &longs)
    :lats(lats), longs(longs)
{
    glEnable(GL_TEXTURE_2D);
    QImage img;
    if (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ.jpg")){
        qWarning("ERROR in loading texture");
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

void Sphere::build()
{
    float step=2*PI/lats;

    for(int i=0;i<lats;++i)
        buildSegment(i,step);
}

void Sphere::changeTexture(int light){
    glEnable(GL_TEXTURE_2D);
    QImage img;
    if(light==0){
    if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ.jpg")){
        qWarning("ERROR in loading texture");
    }}else if(light==2){
        if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ1.jpg")){
            qWarning("ERROR in loading texture");
        }}else if(light==3){
        if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ2.jpg")){
            qWarning("ERROR in loading texture");
        }}else if(light==4){
        if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ3.jpg")){
            qWarning("ERROR in loading texture");
        }}else if(light==5){
        if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ4.jpg")){
            qWarning("ERROR in loading texture");
        }}else if(light==6){
        if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ5.jpg")){
            qWarning("ERROR in loading texture");
        }}else{
        if  (!img.load("/Users/giuseppemendola/Desktop/courses/semester7/graphics/project/img/circ6.jpg")){
            qWarning("ERROR in loading texture");
    }}
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

void Sphere::buildSegment(const int &index, const float &phiStep)
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

void Sphere::set(const Point3d &p, const Point2d &t, PointArray &segment, TextureArray &txt) const
{
    segment.push_back(p);
    assert(t.x()>=0 && t.x()<=1);
    //assert(t.y()>=0 && t.y()<=1);

    txt.push_back(t);
}

void Sphere::draw()
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
