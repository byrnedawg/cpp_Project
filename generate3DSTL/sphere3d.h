#ifndef SPHERE3D_H
#define SPHERE3D_H

#include "shapes3d.h"
#include <qmath.h>

class Sphere3D: public Shapes3D {

private:

    GLfloat radius;
    int NumSectors;

public:
     Sphere3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int NumSectors);

    ~Sphere3D();
    void draw();
    void quad2(GLfloat x,GLfloat y,GLfloat z,GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x4,GLfloat y4,GLfloat z4,int NumSectors, GLfloat radius,GLfloat angle,GLfloat anglez);
    void quad3(GLfloat x,GLfloat y,GLfloat z,GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x4,GLfloat y4,GLfloat z4,int NumSectors, GLfloat radius,GLfloat angle,GLfloat anglez);


 };

#endif // SPHERE3D_H
