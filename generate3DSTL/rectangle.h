#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class RectangleOBJ {
private:
    int r_count;
   // QVector<GLfloat> r_data;

    GLfloat x, y, z, length, width, height;
    void add(const QVector3D &v, const QVector3D &n);
    void face(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4);

public:
    RectangleOBJ(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height);
    ~RectangleOBJ();
    void draw();
    const GLfloat *constData() const { return r_data.constData(); }
    int count() const { return r_count; }
    int vertexCount() const { return r_count / 6; }
    QVector<GLfloat> r_data;

};

#endif // RECTANGLE_H
