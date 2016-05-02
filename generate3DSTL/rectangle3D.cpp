#include "rectangle3D.h"

Rectangle3D::Rectangle3D(GLfloat x, GLfloat y, GLfloat z,
                           GLfloat length, GLfloat width, GLfloat height)
                           : Shapes3D(x, y, z), length(length), width(width), height(height){
    shape_data.resize(216); // 6 values * 6 vertex * 6 faces
    this->draw();
}

Rectangle3D::Rectangle3D(GLfloat x, GLfloat y, GLfloat z,
                           GLfloat length, GLfloat width, GLfloat height, GLfloat thickness)
                           : Shapes3D(x, y, z), length(length), width(width), height(height), thickness(thickness){
    shape_data.resize(576); // 6 values * 6 vertex * 16 faces
    this->extrude();
}

Rectangle3D::Rectangle3D(GLfloat x, GLfloat y, GLfloat z,
                           GLfloat length, GLfloat width, GLfloat height,GLfloat offsetX,GLfloat offsetY)
                           : Shapes3D(x, y, z), length(length), width(width), height(height),offsetX(offsetX),offsetY(offsetY){
    shape_data.resize(216); // 6 values * 6 vertex * 6 faces
    this->offset();
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

void Rectangle3D::extrude(){
    GLfloat x1 = x;
    GLfloat y1 = y;
    GLfloat x2 = x + length;
    GLfloat y2 = y;
    GLfloat x3 = x + length;
    GLfloat y3 = y + width;
    GLfloat x4 = x;
    GLfloat y4 = y + width;

    GLfloat x5 = x + thickness;
    GLfloat y5 = y + thickness;
    GLfloat x6 = x + length - thickness;
    GLfloat y6 = y + thickness;
    GLfloat x7 = x + length - thickness;
    GLfloat y7 = y + width - thickness;
    GLfloat x8 = x + thickness;
    GLfloat y8 = y + width - thickness;
    GLfloat z2 = z + height;

    face(x1, y1, z2, x2, y2, z2, x6, y6, z2, x5, y5, z2); // top 1
    face(x2, y2, z2, x3, y3, z2, x7, y7, z2, x6, y6, z2); // top 2
    face(x3, y3, z2, x4, y4, z2, x8, y8, z2, x7, y7, z2); // top 3
    face(x4, y4, z2, x1, y1, z2, x5, y5, z2, x8, y8, z2); // top 4

    face(x1, y1, z, x5, y5, z, x6, y6, z, x2, y2, z); // bottom 1
    face(x2, y2, z, x6, y6, z, x7, y7, z, x3, y3, z); // bottom 2
    face(x3, y3, z, x7, y7, z, x8, y8, z, x4, y4, z); // bottom 3
    face(x4, y4, z, x8, y8, z, x5, y5, z, x1, y1, z); // bottom 4

    face(x5, y5, z2, x5, y5, z, x8, y8, z, x8, y8, z2); // inside 1
    face(x8, y8, z2, x8, y8, z, x7, y7, z, x7, y7, z2); // inside 2
    face(x7, y7, z2, x7, y7, z, x6, y6, z, x6, y6, z2); // inside 3
    face(x6, y6, z2, x6, y6, z, x5, y5, z, x5, y5, z2); // inside 4

    face(x1, y1, z, x1, y1, z2, x4, y4, z2, x4, y4, z); // width side
    face(x2, y2, z, x3, y3, z, x3, y3, z2, x2, y2, z2); // width side
    face(x1, y1, z, x2, y2, z, x2, y2, z2, x1, y1, z2); // length side
    face(x4, y4, z, x4, y4, z2, x3, y3, z2, x3, y3, z); // length side
}

void Rectangle3D::offset(){
    GLfloat x1 = x;
    GLfloat y1 = y;
    GLfloat z1 = z;
    GLfloat x2 = x + length;
    GLfloat y2 = y;
    GLfloat z2=z;
    GLfloat x3 = x + length;
    GLfloat y3 = y + width;
    GLfloat z3=z;
    GLfloat x4 = x;
    GLfloat y4 = y + width;
    GLfloat z4 = z;

    GLfloat x5 = x1+offsetX;
    GLfloat y5 = y1+offsetY;
    GLfloat z5 = z1+height;
    GLfloat x6 = x2+offsetX;
    GLfloat y6 = y2+offsetY;
    GLfloat z6=z2+height;
    GLfloat x7 = x3+offsetX;
    GLfloat y7 = y3+offsetY;
    GLfloat z7 = z3+height;
    GLfloat x8 = x4+offsetX;
    GLfloat y8 = y4+offsetY;
    GLfloat z8 = z4+height;

    face(x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4);
    face(x5,y5,z5,x6,y6,z6,x7,y7,z7,x8,y8,z8);
    face(x1,y1,z1,x2,y2,z2,x6,y6,z6,x5,y5,z5);
    face(x2,y2,z2,x3,y3,z3,x7,y7,z7,x6,y6,z6);
    face(x3,y3,z3,x4,y4,z4,x8,y8,z8,x7,y7,z7);
    face(x1,y1,z1,x5,y5,z5,x8,y8,z8,x4,y4,z4);


/*
    face(x1, y1, z, x4, y4, z, x3, y3, z, x2, y2, z);   //bottom  1,4,3,2
    face(x1, y1, z2, x2, y2, z2, x3, y3, z2, x4, y4, z2); // top   5,6,7,8
    face(x1, y1, z, x1, y1, z2, x4, y4, z2, x4, y4, z); // width side 1,5,8,4
    face(x2, y2, z, x3, y3, z, x3, y3, z2, x2, y2, z2); // width side
    face(x1, y1, z, x2, y2, z, x2, y2, z2, x1, y1, z2); // length side
    face(x4, y4, z, x4, y4, z2, x3, y3, z2, x3, y3, z); // length side
    */
}
