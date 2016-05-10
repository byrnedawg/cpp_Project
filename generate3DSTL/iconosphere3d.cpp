//Author: Gregory Byrne

#include "iconosphere3d.h"

Iconosphere3D::Iconosphere3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius,
                        int NumSectors) : Shapes3D(x,y,z),
                        radius(radius),  NumSectors(NumSectors){

    shape_data.resize(360 * 4 * NumSectors); // 6 values * 3points * 20 triangles *NumSectors
    this->draw();
}

Iconosphere3D :: ~Iconosphere3D(){

}

void Iconosphere3D::draw(){

    GLfloat x0 = x ;
    GLfloat y0 = y - radius/2;
    GLfloat z0 = z + radius;
    GLfloat x1 = x ;
    GLfloat y1 = y + radius/2;
    GLfloat z1 = z + radius;
    GLfloat x2 = x ;
    GLfloat y2 = y - radius/2;
    GLfloat z2 = z - radius;
    GLfloat x3 = x ;
    GLfloat y3 = y + radius/2;
    GLfloat z3 = z - radius;
    GLfloat x4 = x + radius ;
    GLfloat y4 = y ;
    GLfloat z4 = z - radius/2;
    GLfloat x5 = x + radius;
    GLfloat y5 = y ;
    GLfloat z5 = z + radius/2;
    GLfloat x6 = x - radius;
    GLfloat y6 = y ;
    GLfloat z6 = z - radius/2;
    GLfloat x7 = x - radius;
    GLfloat y7 = y ;
    GLfloat z7 = z + radius/2;
    GLfloat x8 = x - radius/2;
    GLfloat y8 = y + radius;
    GLfloat z8 = z ;
    GLfloat x9 = x + radius/2;
    GLfloat y9 = y + radius ;
    GLfloat z9 = z ;
    GLfloat x10 = x - radius/2 ;
    GLfloat y10 = y - radius;
    GLfloat z10 = z;
    GLfloat x11 = x + radius/2 ;
    GLfloat y11 = y - radius;
    GLfloat z11 = z;

    // define 20 triangles
    tri(x0, y0, z0, x1, y1, z1, x5, y5, z5);
    tri(x0, y0, z0, x5, y5, z5, x11, y11, z11);
    tri(x0, y0, z0, x11, y11, z11, x10, y10, z10);
    tri(x0, y0, z0, x10, y10, z10, x7, y7, z7);
    tri(x0, y0, z0, x7, y7, z7, x1, y1, z1);

    tri(x3, y3, z3, x4, y4, z4, x9, y9, z9);
    tri(x3, y3, z3, x2, y2, z2, x4, y4, z4);
    tri(x3, y3, z3, x6, y6, z6, x2, y2, z2);
    tri(x3, y3, z3, x8, y8, z8, x6, y6, z6);
    tri(x3, y3, z3, x9, y9, z9, x8, y8, z8);

    tri(x1, y1, z1, x9, y9, z9, x5, y5, z5);
    tri(x5, y5, z5, x4, y4, z4, x11, y11, z11);
    tri(x11, y11, z11, x2, y2, z2, x10, y10, z10);
    tri(x10, y10, z10, x6, y6, z6, x7, y7, z7);
    tri(x7, y7, z7, x8, y8, z8, x1, y1, z1);

    tri(x4, y4, z4, x5, y5, z5, x9, y9, z9);
    tri(x2, y2, z2, x11, y11, z11, x4, y4, z4);
    tri(x6, y6, z6, x10, y10, z10, x2, y2, z2);
    tri(x8, y8, z8, x7, y7, z7, x6, y6, z6);
    tri(x9, y9, z9, x1, y1, z1, x8, y8, z8);

/*
    GLfloat midx1;
    GLfloat midy1;
    GLfloat midz1;
    GLfloat midx2;
    GLfloat midy2;
    GLfloat midz2;
    GLfloat midx3;
    GLfloat midy3;
    GLfloat midz3;

    midpoint(x4, y4, z4, x5, y5, z5, midx1, midy1, midz1);
    midpoint(x4, y4, z4, x9, y9, z9, midx2, midy2, midz2);
    midpoint(x5, y5, z5, x9, y9, z9, midx3, midy3, midz3);

    //tri(x4, y4, z4, midx1, midy1, midz1, midx2, midy2, midz2);
  //  tri(midx1, midy1, midz1, midz3, midz3, midz3, midx2, midy2, midz2);
   // tri(midx1, midy1, midz1, midx3, midy3, midz3, midx2, midy2, midz2);
    //tri(x4, y4, z4, midx1, midy1, midz1, midx2, midy2, midz2);

*/

}

void Iconosphere3D::midpoint(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2,
                                                     GLfloat& midX, GLfloat& midY, GLfloat& midZ){
    midX = (x1 + x2) /2.0;
    midY = (y1 + y2) /2.0;
    midZ = (z1 + z2) /2.0;

}
