#ifndef TCUBE_H
#define TCUBE_H

#include <shapes3d.h>
//#include<cube2.h>
#include<qmath.h>
#include <cmath>
#include <iostream>
using namespace std;

class Tcube :public Shapes3D
{
private:
   // GLfloat x,y,z;
    GLfloat length,width,height,rotation;
    int slice;
    QVector3D orig;
    QVector3D p1,p2,p3,p4,p5,p6,p7,p8;

public:

    ~Tcube();
    Tcube(GLfloat x,GLfloat y,GLfloat z,GLfloat length, GLfloat width, GLfloat height, GLfloat rotation, int slice);
   // Tcube(GLfloat x,GLfloat y,GLfloat z,GLfloat length, GLfloat width, GLfloat height, GLfloat rotation, GLfloat incline,int slice);

    void draw();
};

#endif // TCUBE_H
