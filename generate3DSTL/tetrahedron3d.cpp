//Author: Gregory Byrne

#include "tetrahedron3d.h"

Tetrahedron3D::Tetrahedron3D( GLfloat x, GLfloat y, GLfloat z, GLfloat x2,
               GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3,
               GLfloat height) : Shapes3D(x, y, z), x2(x2), y2(y2), z2(z2),
                x3(x3), y3(y3), z3(z3), height(height){
    shape_data.resize(72); // 6 values * 3 vertex * 4 faces
    this->draw();
}

Tetrahedron3D :: ~Tetrahedron3D() {

}

void Tetrahedron3D::draw(){
    GLfloat x4 = (x+x2+x3)/3; //find centroid x
    GLfloat y4 = (y+y2+y3)/3; //find centroid y
    GLfloat z4 = (z+z2+z3)/3 + height; //find centroid z

    //define the 4 facets
    tri(x, y, z, x3, y3, z3, x2, y2, z2); //right hand rule with to find correct normals
    tri(x4, y4, z4, x3, y3, z3, x, y, z);
    tri(x4, y4, z4, x, y, z, x2, y2, z2);
    tri(x4, y4, z4, x2, y2, z2, x3, y3, z3);
}
