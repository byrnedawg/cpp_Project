//Author: Shaotu Jia

#ifndef TCUBE_H
#define TCUBE_H

#include <shapes3d.h>
// Create a cube which is sliced and twisted
class Tcube :public Shapes3D
{
private:
   // GLfloat x,y,z;
    GLfloat length,width,height,rotation;
    int slice; // how many slice the cube is choped
    QVector3D orig; //origin
    QVector3D p1,p2,p3,p4,p5,p6,p7,p8; //six vertex in each sliced cube

public:

    ~Tcube();
    Tcube(GLfloat x,GLfloat y,GLfloat z,GLfloat length, GLfloat width, GLfloat height, GLfloat rotation, int slice);

    void draw();
};

#endif // TCUBE_H
