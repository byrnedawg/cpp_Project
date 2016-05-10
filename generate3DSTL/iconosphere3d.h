//Author: Gregory Byrne

#ifndef ICONOSPHERE3D_H
#define ICONOSPHERE3D_H

#include "shapes3d.h"

class Iconosphere3D: public Shapes3D {

private:

    GLfloat  radius;
    int NumSectors;

public:
    //define iconosphere
    Iconosphere3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int NumSectors);

    ~Iconosphere3D();
    void draw();

    void midpoint(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2,
                                    GLfloat& midX, GLfloat& midY, GLfloat& midZ);
};
#endif // ICONOSPHERE3D_H
