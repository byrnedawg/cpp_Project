//Author: Gregory Byrne for Cylinder and Extruded Cylinder with "draw()" and "extrude()" functions
//        Shaotu Jia for inclined Cylinder and Rotate Cylinder with "incline()" and "rotate()" functions


#ifndef CYLINDER3D_H
#define CYLINDER3D_H

#include "shapes3d.h"
#include <qmath.h>

/* Class Cylinder3D is inherited from Shape3D
 * The first Constructor is to draw straight Cylinder
 * The second Constructor is to draw straight cylinder with extursion method
 * The three Constructor is to draw clylinder which inclines in X or Y direction
 * The four Constructor is to draw cylinder which rotates along a axis
 */

class Cylinder3D: public Shapes3D {

private:

    GLfloat  radius, height, inRadius, outRadius;
    int NumSectors;
    GLfloat inclineX,inclineY,rotation;
    GLfloat xz,yz; // the x,y of rotation axis

public:
     //define cyclinder x y z radius height and numsectors or smoothness num sectors can be used to make hexagon or octagon
    Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors);
    //define cyclinder with center cut out x y z inRadius outRadius height and numsectors
     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat inRadius, GLfloat outRadius, GLfloat height, int NumSectors);

     Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLfloat inclineX, GLfloat inclineY, int NumSectors);
     //incline in x and y axis
     Cylinder3D(GLfloat xz,GLfloat yz,GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, GLdouble rotation,int NumSectors);
     //rotate based on the z-axis of global coordinate

     ~Cylinder3D();
    void draw();
    void extrude();
    void incline();
    void rotate();
};

#endif // CYLINDER3D_H
