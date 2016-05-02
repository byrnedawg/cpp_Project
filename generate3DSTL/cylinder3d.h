#ifndef CYLINDER3D_H
#define CYLINDER3D_H

#include "shapes3d.h"
#include <qmath.h>

class Cylinder3D: public Shapes3D {

private:

    GLfloat  radius, height, inRadius, outRadius;
    int NumSectors;
    GLfloat inclineX,inclineY,rotation;
    GLfloat xz,yz; // the x,y of rotation axis

public:
     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors);

     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat inRadius, GLfloat outRadius, GLfloat height, int NumSectors);

     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLfloat inclineX, GLfloat inclineY, int NumSectors);
     //incline is x and y axis
     Cylinder3D(GLfloat xz,GLfloat yz,GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLdouble rotation,int NumSectors);
     //rotate based on the z-axis of global coordinate

     ~Cylinder3D();
    void draw();
    void extrude();
    void incline();
    void rotate();
};

#endif // CYLINDER3D_H
