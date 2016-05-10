//Author: Gregory Byrne

#ifndef SHAPES3D_H
#define SHAPES3D_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class Shapes3D
{
private:

protected:
    GLfloat x, y, z;//x,y,z are the origin of local coordinate system for every shape
                    // This origin keeps all other vertex with postive coordinate in the local coordinate system
    Shapes3D(GLfloat x, GLfloat y, GLfloat z);
    ~Shapes3D();

    virtual void add(const QVector3D &v, const QVector3D &n);

    //generate facet with 3 points and the same normal
    virtual void tri(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2,
                     GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3);

    //generate face with 4 points will create two facets with the same normal
    virtual void face(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2,
                 GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3,
                 GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4);

    virtual void draw() = 0;
    //virtual void volume() = 0;

public:

    QVector<GLfloat> shape_data;
    int shape_count;
};

#endif // SHAPES3D_H
