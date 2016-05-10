//Author: Gregory Byrne

#ifndef TRIANGLE3D_H
#define TRIANGLE3D_H


#include "shapes3d.h"

class Triangle3D : public Shapes3D {

private:

    GLfloat length, width, height;

public:
    // generate a ramp like triangle
    Triangle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height);
    ~Triangle3D();
    void draw();

};


#endif // TRIANGLE3D_H
