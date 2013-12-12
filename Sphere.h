#ifndef SPHERE_H
#define SPHERE_H
#include <QtOpenGL>
#include "Point3.h"
#include "Point2.h"

class Sphere
{
private:
    typedef std::vector<Point3d> PointArray;
    typedef std::vector<Point2d> TextureArray;

    int lats, longs;
    std::vector<PointArray> strips;
    std::vector<TextureArray> textures;

    void build();
    void buildSegment(const int &index, const float &phiStep);
    void set(const Point3d &p, const Point2d &t, PointArray &segment, TextureArray &txt) const;
    GLuint name;

public:
    Sphere(const int &lats=20, const int &longs=10);
    void changeTexture(int light);

    void draw();
};

#endif // SPHERE_H
