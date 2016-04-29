#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shapes3d.h"

class Rectangle3D : public Shapes3D {

private:

    GLfloat length, width, height;

public:
    Rectangle3D(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height);
    ~Rectangle3D();
    void draw();
   // const GLfloat *constData() const { return r_data.constData(); }
   // int count() const { return r_count; }
   // int vertexCount() const { return r_count / 6; }
    //QVector<GLfloat> r_data;

};

#endif // RECTANGLE_H
