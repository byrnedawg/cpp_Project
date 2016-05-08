#ifndef PYRAMID3D_H
#define PYRAMID3D_H

#include "shapes3d.h"

class Pyramid3D: public Shapes3D {

private:

    GLfloat length, width, height;

public:
     Pyramid3D(  GLfloat x, GLfloat y, GLfloat z, GLfloat length,
                 GLfloat width, GLfloat height);

    ~Pyramid3D();
    void draw();
 };

#endif // PYRAMID3D_H
