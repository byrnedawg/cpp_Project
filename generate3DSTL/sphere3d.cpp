#include "sphere3d.h"

Sphere3D::Sphere3D(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int NumSectors) : Shapes3D(x, y, z), radius(radius), NumSectors(NumSectors){
    shape_data.resize(2048*NumSectors); // 6 * 3 * 4 + 6 * 6
    this->draw();
}

Sphere3D :: ~Sphere3D() {

}

void Sphere3D::draw(){

    for (int j=0; j<NumSectors;j++){
        GLfloat anglez=(j*M_PI)/(NumSectors*2);     //anglez is the angle between x-y plane and vector from origin to the point on spherical surface
                                                     //Range[0-90degree]
        GLfloat angle = (0*2 * M_PI) / NumSectors; //angle is the angle between x-axis and point which is on the spherical surface
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        GLfloat x1 = radius * angleCos*qCos(anglez) + x;   //initialze (x1,y1,z1) and (x4,y4,z4)
        GLfloat y1 = radius * angleSin*qCos(anglez) + y;
        GLfloat z1 =radius * qSin(anglez)+z;
        GLfloat x4=0.0;
        GLfloat y4 = 0.0;
        GLfloat z4=0.0;
        GLfloat zn1=0.0;   //zn1 and zn4 are the reflection of coordinate of (x1,y1,z1) and (x4,y4,z4) based on x-y plane
        GLfloat zn4=0.0;

        for (int i=0; i < NumSectors; ++i) {

            angle = (i * 2 * M_PI) / NumSectors;

            x4 = radius * qCos(angle+2*M_PI/NumSectors)*qCos(anglez+2*M_PI/NumSectors) + x;
            y4 = radius * qSin(angle+2*M_PI/NumSectors)*qCos(anglez+2*M_PI/NumSectors) + y;
            z4 = radius * qSin(anglez+2*M_PI/NumSectors) + z;

            quad2(x,y,z,x1,y1,z1,x4,y4,z4,NumSectors,radius,angle,anglez);
            zn1=-z1+2*z;
            zn4=-z4+2*z;
         //   quad2(x,y,z,x1,y1,zn1,x4,y4,zn4,NumSectors,radius,angle,anglez);  //draw the reflection hemi-sphere based on x-y plane
            quad2(x,y,z,x1,y1,zn1,x4,y4,zn4,NumSectors,radius,angle,anglez);  //draw the reflection hemi-sphere based on x-y plane
            x1=radius*qCos(angle+2*M_PI/NumSectors)*qCos(anglez)+x;
            y1=radius*qSin(angle+2*M_PI/NumSectors)*qCos(anglez)+y;
            z1=radius * qSin(anglez)+z;

            }
        x1 = x4;
        y1 = y4;
        z1 = z4;
        zn1=zn4;

    }
}

void Sphere3D::quad2(GLfloat x,GLfloat y,GLfloat z,GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x4,GLfloat y4,GLfloat z4,int NumSectors, GLfloat radius,GLfloat angle,GLfloat anglez){

    GLfloat alpha=2*M_PI/NumSectors;
    QVector3D n= QVector3D((x1+x4)/2-x,(y1+y4)/2-y,(z1+z4)/2-z);
   //QVector3D n = QVector3D::normal(QVector3D(radius*qCos(anglez+alpha*qCos(angle))+x - x1, radius*qCos(anglez+alpha)*qSin(angle)+y-y1, z4-z1), QVector3D(radius*qCos(angle+alpha)+x-x1, radius*qSin(angle+alpha)+y-y1, z1-z1));


    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(radius*qCos(anglez+alpha)*qCos(angle)+x,radius*qCos(anglez+alpha)*qSin(angle)+y,z4),n);
    add(QVector3D(x4, y4, z4), n);


    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(radius*qCos(angle+alpha)*qCos(anglez)+x, radius*qSin(angle+alpha)*qCos(anglez)+y, z1), n);
    add(QVector3D(x1, y1, z1), n);

    }
