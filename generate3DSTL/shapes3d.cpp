//Author: Gregory Byrne

#include "shapes3d.h"

Shapes3D::Shapes3D(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z), shape_count(0)
{
    shape_data.resize(1); // size of shape_data to start
}

Shapes3D::~Shapes3D(){
    shape_count = 0; //keeps count of how many values are in shape_data
}

// add point data to shape_data 6 values per point x, y, z normal x, normal y, normal z
void Shapes3D::add(const QVector3D &v, const QVector3D &n){
    GLfloat *p = shape_data.data() + shape_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    shape_count += 6;
}
//create triangle with 3 points and a common normal and add it to shape_data
void Shapes3D::tri(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3){
    QVector3D n = QVector3D::normal(QVector3D(x3 - x1, y3 - y1, z3 - z1), QVector3D(x2 - x1, y2 - y1, z2 - z1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x2, y2, z2), n);

}

//create a face with 4 points which is creating 2 triangles and a common normal and add it to shape_data
void Shapes3D::face(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2,
                     GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3,
                     GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4){

    QVector3D n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, z1 - z4), QVector3D(x2 - x4, y2 - y4, z2 - z4));

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);

}


