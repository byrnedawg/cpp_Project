#ifndef DRAW3D_H
#define DRAW3D_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <iostream>
#include <fstream>

using namespace std;

class Draw3D
{
public:
    Draw3D();
    const GLfloat *constData() const { return m_data.constData(); }
    int count() const { return m_count; }
    int vertexCount() const { return m_count / 6; }

    ofstream stlWriter; // output file object to write stl file data

private:
    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat quadThickness);
    void quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat z, GLfloat zHeight);
    void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat extrudeThickness);
    void extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z, GLfloat zHeight);
    void add(const QVector3D &v, const QVector3D &n);
    void rectangle(GLfloat x, GLfloat y, GLfloat L, GLfloat W, GLfloat H);
    void rectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height);
    void extrudedRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height, GLfloat thickness);
    void cylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors);
    void extrudedCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat inRadius, GLfloat outRadius, GLfloat height, int NumSectors);
    void pyramid(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height);

    QVector<GLfloat> m_data;
    int m_count;
};

#endif // LOGO_H
