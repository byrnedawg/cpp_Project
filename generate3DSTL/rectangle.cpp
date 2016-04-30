#include "rectangle.h"

Rectangle3D::Rectangle3D(GLfloat x, GLfloat y, GLfloat z,
                           GLfloat length, GLfloat width, GLfloat height)
                           : Shapes3D(x, y, z), length(length), width(width), height(height){
    shape_data.resize(216); // 6 values * 6 vertex * 6 faces
    this->draw();
}
Rectangle3D::~Rectangle3D(){

}

void Rectangle3D::draw(){
    GLfloat x1 = x;
    GLfloat y1 = y;
    GLfloat x2 = x + length;
    GLfloat y2 = y;
    GLfloat x3 = x + length;
    GLfloat y3 = y + width;
    GLfloat x4 = x;
    GLfloat y4 = y + width;
    GLfloat z2 = z + height;


    face(x1, y1, z, x4, y4, z, x3, y3, z, x2, y2, z);   //bottom
    face(x1, y1, z2, x2, y2, z2, x3, y3, z2, x4, y4, z2); // top
    face(x1, y1, z, x1, y1, z2, x4, y4, z2, x4, y4, z); // width side
    face(x2, y2, z, x3, y3, z, x3, y3, z2, x2, y2, z2); // width side
    face(x1, y1, z, x2, y2, z, x2, y2, z2, x1, y1, z2); // length side
    face(x4, y4, z, x4, y4, z2, x3, y3, z2, x3, y3, z); // length side
}
