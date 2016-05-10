//Author: Shaotu Jia

#ifndef CUBE2_H
#define CUBE2_H
#include "shapes3d.h"

/* This constructor is to draw a cube with arbitary vertex
 */

class Cube2:public Shapes3D
{
private:
    GLfloat x;GLfloat y;GLfloat z;

public:
    QVector3D b1,b2,b3,b4,b5,b6,b7,b8;
    ~Cube2();
    void draw();
    Cube2(QVector3D q1, QVector3D q2, QVector3D q3, QVector3D q4, QVector3D q5, QVector3D q6, QVector3D q7, QVector3D q8);
};

#endif // CUBE2_H
