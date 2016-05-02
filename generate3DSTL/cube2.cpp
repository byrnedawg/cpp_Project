#include "cube2.h"

Cube2::~Cube2()
{

}

Cube2::Cube2(QVector3D q1, QVector3D q2, QVector3D q3, QVector3D q4, QVector3D q5, QVector3D q6, QVector3D q7, QVector3D q8):Shapes3D(q1.x(),q1.y(),q1.z()),b1(q1),b2(q2),b3(q3),b4(q4),b5(q5),b6(q6),b7(q7),b8(q8){
    shape_data.resize(216); //6 * 6 * 6
    this->draw();
    //Shapes3D(q1.x(),q1.y(),q1.z());

}

void Cube2::draw(){
    face((GLfloat)b1.x(),(GLfloat)b1.y(),(GLfloat)b1.z(),(GLfloat)b2.x(),(GLfloat)b2.y(),(GLfloat)b2.z(),(GLfloat)b3.x(),(GLfloat)b3.y(),(GLfloat)b3.z(),(GLfloat)b4.x(),(GLfloat)b4.y(),(GLfloat)b4.z());   //bottom
    face((GLfloat)b5.x(),(GLfloat)b5.y(),(GLfloat)b5.z(),(GLfloat)b6.x(),(GLfloat)b6.y(),(GLfloat)b6.z(),(GLfloat)b7.x(),(GLfloat)b7.y(),(GLfloat)b7.z(),(GLfloat)b8.x(),(GLfloat)b8.y(),(GLfloat)b8.z()); // top
    face((GLfloat)b1.x(),(GLfloat)b1.y(),(GLfloat)b1.z(),(GLfloat)b2.x(),(GLfloat)b2.y(),(GLfloat)b2.z(),(GLfloat)b6.x(),(GLfloat)b6.y(),(GLfloat)b6.z(),(GLfloat)b5.x(),(GLfloat)b5.y(),(GLfloat)b5.z()); // width side
    face((GLfloat)b2.x(),(GLfloat)b2.y(),(GLfloat)b2.z(),(GLfloat)b3.x(),(GLfloat)b3.y(),(GLfloat)b3.z(),(GLfloat)b7.x(),(GLfloat)b7.y(),(GLfloat)b7.z(),(GLfloat)b6.x(),(GLfloat)b6.y(),(GLfloat)b6.z()); // width side
    face((GLfloat)b3.x(),(GLfloat)b3.y(),(GLfloat)b3.z(),(GLfloat)b4.x(),(GLfloat)b4.y(),(GLfloat)b4.z(),(GLfloat)b8.x(),(GLfloat)b8.y(),(GLfloat)b8.z(),(GLfloat)b7.x(),(GLfloat)b7.y(),(GLfloat)b7.z()); // length side
    face((GLfloat)b1.x(),(GLfloat)b1.y(),(GLfloat)b1.z(),(GLfloat)b5.x(),(GLfloat)b5.y(),(GLfloat)b5.z(),(GLfloat)b8.x(),(GLfloat)b8.y(),(GLfloat)b8.z(),(GLfloat)b4.x(),(GLfloat)b4.y(),(GLfloat)b4.z()); // length side
}
