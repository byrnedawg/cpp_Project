#ifndef CYLINDER3D_H
#define CYLINDER3D_H

#include "shapes3d.h"
#include <qmath.h>

class Cylinder3D: public Shapes3D {

private:

    GLfloat  radius, height, inRadius, outRadius;
    int NumSectors;

public:
     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors);

     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat inRadius, GLfloat outRadius, GLfloat height, int NumSectors);

    ~Cylinder3D();
    void draw();
    void extrude();
};

#endif // CYLINDER3D_H
