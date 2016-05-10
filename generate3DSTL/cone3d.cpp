// Author: Gregory Byrne

#include "cone3d.h"

Cone3D::Cone3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius,
                      GLfloat height, int NumSectors, bool cap)
                      : Shapes3D(x, y, z), radius(radius), height(height),
                        NumSectors(NumSectors), cap(cap){

    shape_data.resize( 72 * NumSectors); // 6 values * 12 vertex *NumSectors
    this->draw();
}

Cone3D :: ~Cone3D() {

}

void Cone3D::draw(){
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

        if(cap){
            face(x1,y1,z+height, x2, y2, z+height, x3, y3, z+height, x4, y4, z+height); // bottom
        }
            face(x4,y4,z+height, x3, y3, z, x2, y2, z, x1, y1, z+height); // outer cone

    }
}
