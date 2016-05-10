//Author: Gregory Byrne for Rectangle and Extruded Rectangle
//        Shaotu Jia for Inclinded Rectangle

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shapes3d.h"

/* Class Rectangle3D is inherited from Class Shapes3D
 * There are three constructors in Rectangle3D class for draw different 3D Rectangles
 * The first constructor to draw 3D rectangle
 * The second constructor to draw 3D rectangle with extrusion.
 * The third constructor to draw inclined 3D rectangle
 */

class Rectangle3D : public Shapes3D {

private:

    GLfloat length, width, height, thickness;
    GLfloat offsetX,offsetY; //offsetX and offsetY is coordinate difference between bottom and top vertexs

public:
    Rectangle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height);
    Rectangle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height, GLfloat thickness);
    Rectangle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height,GLfloat offsetX,GLfloat offsetY);


    ~Rectangle3D();
    void draw();
    void extrude();
    void offset();

};

#endif // RECTANGLE_H
