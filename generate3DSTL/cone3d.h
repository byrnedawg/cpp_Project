// Author: Gregory Byrne

/* class Cone3D is inherited from Shape3D to create Cone3D shape
 */

#ifndef CONE3D_H
#define CONE3D_H

#include "shapes3d.h"
#include <qmath.h>

class Cone3D: public Shapes3D {

private:
    GLfloat radius, height;
    int NumSectors;
    bool cap;

public:
    //define cone with or without cap at the base of the cone
     Cone3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors, bool cap);

    ~Cone3D();

    void draw();
};


#endif // CONE3D_H
