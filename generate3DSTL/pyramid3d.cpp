#include "pyramid3d.h"

Pyramid3D::Pyramid3D( GLfloat x, GLfloat y, GLfloat z, GLfloat length,
                      GLfloat width, GLfloat height) : Shapes3D(x, y, z),
                      length(length), width(width), height(height){

    this->draw();
}

Pyramid3D :: ~Pyramid3D() {

}

void Pyramid3D::draw(){
    GLfloat x1 = x;
    GLfloat y1 = y;
    GLfloat x2 = x + length;
    GLfloat y2 = y;
    GLfloat x3 = x + length;
    GLfloat y3 = y + width;
    GLfloat x4 = x;
    GLfloat y4 = y + width;
    GLfloat x5 = x + (length / 2);
    GLfloat y5 = y + (width / 2);
    GLfloat z5 = z + height;

    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    if(height < 0){
         n = QVector3D::normal(QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(x4 - x1, y4 - y1, 0.0f));

        add(QVector3D(x1, y1, z), n);
        add(QVector3D(x2, y2, z), n);
        add(QVector3D(x4, y4, z), n);

        add(QVector3D(x3, y3, z), n);
        add(QVector3D(x4, y4, z), n);
        add(QVector3D(x2, y2, z), n);

    }else{

        add(QVector3D(x1, y1, z), n);
        add(QVector3D(x4, y4, z), n);
        add(QVector3D(x2, y2, z), n);

        add(QVector3D(x3, y3, z), n);
        add(QVector3D(x2, y2, z), n);
        add(QVector3D(x4, y4, z), n);

    }

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x2 - x5, y2 - y5, z - z5), QVector3D(x1 - x5, y1 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x1 - x5, y1 - y5, z - z5), QVector3D(x2 - x5, y2 - y5, z - z5));
    }

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x2, y2, z ), n);
        add(QVector3D(x1, y1, z), n);

    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x1, y1, z), n);
        add(QVector3D(x2, y2, z ), n);
    }

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x3 - x5, y3 - y5, z - z5), QVector3D(x2 - x5, y2 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x2 - x5, y2 - y5, z - z5), QVector3D(x3 - x5, y3 - y5, z - z5));
    }

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x3, y3, z ), n);
        add(QVector3D(x2, y2, z), n);
    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x2, y2, z), n);
        add(QVector3D(x3, y3, z ), n);
    }

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x4 - x5, y4 - y5, z - z5), QVector3D(x3 - x5, y3 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x3 - x5, y3 - y5, z - z5), QVector3D(x4 - x5, y4 - y5, z - z5));
    }

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x4, y4, z ), n);
        add(QVector3D(x3, y3, z), n);
    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x3, y3, z), n);
        add(QVector3D(x4, y4, z ), n);
    }

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x1 - x5, y1 - y5, z - z5), QVector3D(x4 - x5, y4 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x4 - x5, y4 - y5, z - z5), QVector3D(x1 - x5, y1 - y5, z - z5));
    }

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x1, y1, z ), n);
        add(QVector3D(x4, y4, z), n);
    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x4, y4, z), n);
        add(QVector3D(x1, y1, z ), n);
    }


}


