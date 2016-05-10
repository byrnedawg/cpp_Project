//Author: Gregory Byrne

#ifndef TETRAHEDRON3D_H
#define TETRAHEDRON3D_H

#include "shapes3d.h"

class Tetrahedron3D: public Shapes3D {

private:

    GLfloat x2, y2, z2, x3, y3, z3, height;

public:
    //create tetrahedron shape with 3 points and a height
     Tetrahedron3D( GLfloat x, GLfloat y, GLfloat z, GLfloat x2,
                    GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3,
                    GLfloat z3, GLfloat height);

    ~Tetrahedron3D();
    void draw();
};


#endif // TETRAHEDRON3D_H
