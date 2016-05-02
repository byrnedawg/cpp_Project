#ifndef DRAW3D_H
#define DRAW3D_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>
#include <iostream>
#include <fstream>
#include "rectangle3D.h"
#include "tetrahedron3d.h"
#include "cylinder3d.h"
#include "pyramid3d.h"
#include "cone3d.h"
#include "triangle3d.h"
#include "sphere3d.h"
#include "iconosphere3d.h"

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
    void print3D(Shapes3D& a);
    QVector<GLfloat> m_data;
    int m_count;
    int vectorSize;

    //Not needed anymore add is handled in the shape class
    void add(const QVector3D &v, const QVector3D &n);

    /****************************************************************************************************************/
    //Writen by Shaotu Jia
    void sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat Radius, int Numsectors);
    void quad2(GLfloat x, GLfloat y, GLfloat z, GLfloat x1, GLfloat y1, GLfloat z2, GLfloat x4, GLfloat y4, GLfloat z4, int NumSectors, GLfloat radius, GLfloat angle, GLfloat anglez);

    /***************************************************************************************************************************************************************************************/

};

#endif // DRAW3D_H
