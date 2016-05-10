//Author: Gregory Byrne for Cylinder and Extruded Cylinder with "draw()" and "extrude()" functions
//        Shaotu Jia for inclined Cylinder and Rotate Cylinder with "incline()" and "rotate()" functions

#include "cylinder3d.h"
#include <cmath>
#include<iostream>



Cylinder3D::Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius,
                       GLfloat height, int NumSectors) : Shapes3D(x,y,z),
                        radius(radius), height(height), NumSectors(NumSectors){

    shape_data.resize(108 * NumSectors); // 6 values * 18 vertex *NumSectors
    this->draw();
}

Cylinder3D::Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat inRadius,
                       GLfloat outRadius, GLfloat height, int NumSectors) : Shapes3D(x,y,z),
                        inRadius(inRadius), outRadius(outRadius), height(height), NumSectors(NumSectors){

    shape_data.resize(144 * NumSectors); // 6 values * 24 vertex *NumSectors
    this->extrude();
}

Cylinder3D::Cylinder3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius,
                       GLfloat height, GLfloat inclineX,GLfloat inclineY,int NumSectors) : Shapes3D(x,y,z),
                        radius(radius), height(height),inclineX(inclineX),inclineY(inclineY),NumSectors(NumSectors){

    shape_data.resize(108 * NumSectors* NumSectors); // 6 values * 18 vertex *NumSectors*NumSectors
    this->incline();
}

Cylinder3D::Cylinder3D(GLfloat xz, GLfloat yz, GLfloat x, GLfloat y, GLfloat z, GLfloat radius,
                       GLfloat height, GLdouble rotation, int NumSectors) : xz(xz),yz(yz),Shapes3D(x,y,z),
                        radius(radius), height(height), rotation(rotation),NumSectors(NumSectors){

    shape_data.resize(108 * NumSectors*NumSectors); // 6 values * 18 vertex *NumSectors
    this->rotate();
}

Cylinder3D :: ~Cylinder3D() {
    //shape_data.clear();
}

void Cylinder3D::draw(){
    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        GLfloat x1 = radius * angleSin + x;
        GLfloat y1 = radius * angleCos + y;
        GLfloat x2 = 0 * angleSin + x;
        GLfloat y2 = 0 * angleCos + y;

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        GLfloat x3 = 0 * angleSin + x;
        GLfloat y3 = 0 * angleCos + y;
        GLfloat x4 = radius * angleSin + x;
        GLfloat y4 = radius * angleCos + y;

        face(x4,y4,z, x3, y3, z, x2, y2, z, x1, y1, z); // bottom
        face(x1,y1, z+height, x2, y2, z+height, x3, y3, z+height, x4, y4, z+height); // top

        face(x1,y1,z, x1, y1, z+height, x4, y4, z+height, x4, y4, z); // cylinder sides


    }

}

void Cylinder3D::extrude(){
    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        GLfloat x1 = outRadius * angleSin + x;
        GLfloat y1 = outRadius * angleCos + y;
        GLfloat x2 = inRadius * angleSin + x;
        GLfloat y2 = inRadius * angleCos + y;

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        GLfloat x3 = inRadius * angleSin + x;
        GLfloat y3 = inRadius * angleCos + y;
        GLfloat x4 = outRadius * angleSin + x;
        GLfloat y4 = outRadius * angleCos + y;


        face(x4,y4,z, x3, y3, z, x2, y2, z, x1, y1, z); // bottom
        face(x1,y1,z+height, x2, y2, z+height, x3, y3,z+height, x4, y4, z+height); // top

        face(x1,y1,z, x1, y1,z+height, x4, y4, z+height, x4, y4, z); // cylinder sides

        face(x3,y3,z, x3, y3,z+height, x2, y2, z+height, x2, y2, z); // inner sides

    }
}

void Cylinder3D::rotate(){
    GLfloat slice=height/NumSectors;
    GLfloat angler=rotation/NumSectors;
    GLfloat length=sqrt((x-xz)*(x-xz)+(y-yz)*(y-yz));

    for(int j=0;j<NumSectors;++j){
        x=xz+length*qCos(angler*j);
        y=yz+length*qSin(angler*j);


        for (int i = 0; i < NumSectors; ++i) {

            GLfloat angle = (i * 2 * M_PI) / NumSectors;
            GLfloat angleSin = qSin(angle);
            GLfloat angleCos = qCos(angle);
            GLfloat x1 = radius * angleSin + x;
            GLfloat y1 = radius * angleCos + y;
            GLfloat x2 = 0 * angleSin + x;
            GLfloat y2 = 0 * angleCos + y;

            angle = ((i + 1) * 2 * M_PI) / NumSectors;
            angleSin = qSin(angle);
            angleCos = qCos(angle);
            GLfloat x3 = 0 * angleSin + x;
            GLfloat y3 = 0 * angleCos + y;
            GLfloat x4 = radius * angleSin + x;
            GLfloat y4 = radius * angleCos + y;


            face(x4,y4,z, x3, y3, z, x2, y2, z, x1, y1, z); // bottom
            face(x1,y1, z+slice, x2, y2, z+slice, x3, y3, z+slice, x4, y4, z+slice); // top

            face(x1,y1,z, x1, y1, z+slice, x4, y4, z+slice, x4, y4, z); // cylinder sides

       }
        z=z+slice;

    }

}

void Cylinder3D::incline(){
    GLfloat slice=height/NumSectors;

    for(int j=0;j<NumSectors;j++){
        x=x+slice/qTan(inclineX);
        y=y+slice/qTan(inclineY);
        z=z+slice;
        for (int i = 0; i < NumSectors; ++i) {

            GLfloat angle = (i * 2 * M_PI) / NumSectors;
            GLfloat angleSin = qSin(angle);
            GLfloat angleCos = qCos(angle);
            GLfloat x1 = radius * angleSin + x;
            GLfloat y1 = radius * angleCos + y;
            GLfloat x2 = 0 * angleSin + x;
            GLfloat y2 = 0 * angleCos + y;

            angle = ((i + 1) * 2 * M_PI) / NumSectors;
            angleSin = qSin(angle);
            angleCos = qCos(angle);
            GLfloat x3 = 0 * angleSin + x;
            GLfloat y3 = 0 * angleCos + y;
            GLfloat x4 = radius * angleSin + x;
            GLfloat y4 = radius * angleCos + y;

            face(x4,y4,z, x3, y3, z, x2, y2, z, x1, y1, z); // bottom
            face(x1,y1, z+slice, x2, y2, z+slice, x3, y3, z+slice, x4, y4, z+slice); // top

            face(x1,y1,z, x1, y1, z+slice, x4, y4, z+slice, x4, y4, z); // cylinder sides
       }

    }

}
