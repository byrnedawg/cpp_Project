#include "rectangle.h"

RectangleOBJ::RectangleOBJ(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height) :x(x), y(y), z(z), length(length), width(width), height(height), r_count(0){
    r_data.resize(6*6*6);
    this->draw();
}
RectangleOBJ::~RectangleOBJ(){
    r_count = 0;
}

void RectangleOBJ::add(const QVector3D &v, const QVector3D &n){
    GLfloat *p = r_data.data() + r_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    r_count += 6;
}

void RectangleOBJ::face(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4){
    QVector3D n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, z1 - z4), QVector3D(x2 - x4, y2 - y4, z2 - z4));

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);

    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);

}

void RectangleOBJ::draw(){
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
