//Author: Gregory Byrne & Shaotu Jia

#ifndef DRAW3D_H
#define DRAW3D_H

#include <qopengl.h>
#include <stdlib.h>
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
#include "cube2.h"
#include "tcube.h"
#include "window.h"


using namespace std;

class Draw3D
{
public:
    Draw3D();
    const GLfloat *constData() const { return m_data.constData(); } //export model data
    int count() const { return m_count; } // keeps count of model data
    int vertexCount() const { return m_count / 6; } // keeps count of vertex
    void print3D(Shapes3D& a); //adds shape data to stl file and model data
    void closeSTLWriter(); // closes the stl file
    void promptUserInput(); // ask user to input shapes into model
    ofstream stlWriter; // output file object to write stl file data

private:
   // void print3D(Shapes3D& a);
    QVector<GLfloat> m_data;
    int m_count;
    int vectorSize;
};

#endif // DRAW3D_H
