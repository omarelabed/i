#ifndef EYE_H
#define EYE_H
#include <QtOpenGL>
#include "Point3.h"
#include "Point2.h"


class Eye
{
private:
    typedef std::vector<Point3d> PointArray;
    typedef std::vector<Point2d> TextureArray;
   // typedef std::vector<QImage> ImgTextureArray;


    GLuint name;
    int lats, longs;
    std::vector<PointArray> strips;
    std::vector<TextureArray> textures;


    void build();
    void buildSegment(const int &index, const float &phiStep);
    void set(const Point3d &p, const Point2d &t, PointArray &segment, TextureArray &txt) const;
public:
    *Eye(const int &lats=20, const int &longs=10);
    void changeTexture(int light);
    void draw();
};

#endif // EYE_H
