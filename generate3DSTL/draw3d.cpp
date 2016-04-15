#include "draw3d.h"
#include <qmath.h>

Draw3D::Draw3D()
    : m_count(0)
{
    m_data.resize(2500 * 6); //allocate space for data

    //Define 3D shapes to be drawn and outputed to stl file named model.stl
    //Draw Model below ................................................
    stlWriter.open ("model.stl"); //name of stl file
    stlWriter << "solid model\n"; //first line of stl file

    //3D figures in stl file and 3D model space

    rectangle(0,0,-0.1f,0.4f,0.25f,0.2f); //rectangle x, y, z, length, width, height
    rectangle(0,0,0.1f,0.2f,0.2f,0.3f); //rectangle x, y, z, length, width, height
    rectangle(0,.2f, -0.2f, 0.2f, 0.5f, .07f);
    rectangle(-.3,-.2f, -0.2f, 0.2f, 0.5f, .07f);

    //Done with 3D model
    stlWriter << "endsolid model\n"; //last line of stl file
    stlWriter.close(); // close stl file
}


    //Done drawing model .....................................................



/*
    const int NumSectors = 100; //100

    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        const GLfloat x5 = 0.30f * angleSin;
        const GLfloat y5 = 0.30f * angleCos;
        const GLfloat x6 = 0.20f * angleSin; //.20
        const GLfloat y6 = 0.20f * angleCos; //.20

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        const GLfloat x7 = 0.20f * angleSin; //.20
        const GLfloat y7 = 0.20f * angleCos; //.20
        const GLfloat x8 = 0.30f * angleSin;
        const GLfloat y8 = 0.30f * angleCos;

    }
    // GLfloat thickness22 = 0.1f;
    //    quad(x5, y5, x6, y6, x7, y7, x8, y8, thickness22);

      //  extrude(x6, y6, x7, y7, thickness22);
        //extrude(x8, y8, x5, y5, thickness22);
}
*/
//Add the vertexes for the normal n and the vertex v from the 3D shapes definition and output the vertex values to the stl file
void Draw3D::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
    stlWriter << "vertex " << v.x() << " " << v.y() << " " << v.z() <<"\n"; //prints out vertex to stl file
}
//Draw a quad which is a set of 4 triangles so that they create rectanglular surfaces and output the vertex information into a stl file in the correct format
void Draw3D::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat quadThickness)
{
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, -quadThickness), n);
    add(QVector3D(x4, y4, -quadThickness), n);
    add(QVector3D(x2, y2, -quadThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x3, y3, -quadThickness), n);
    add(QVector3D(x2, y2, -quadThickness), n);
    add(QVector3D(x4, y4, -quadThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x4, y4, quadThickness), n);
    add(QVector3D(x1, y1, quadThickness), n);
    add(QVector3D(x2, y2, quadThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, quadThickness), n);
    add(QVector3D(x3, y3, quadThickness), n);
    add(QVector3D(x4, y4, quadThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

//Draw a quad which is a set of 4 triangles so that they create rectanglular surfaces with defined z and output the vertex information into a stl file in the correct format
void Draw3D::quad(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3, GLfloat x4, GLfloat y4, GLfloat z, GLfloat zHeight){
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, z), n);
    add(QVector3D(x4, y4, z), n);
    add(QVector3D(x2, y2, z), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x3, y3, z), n);
    add(QVector3D(x2, y2, z), n);
    add(QVector3D(x4, y4, z), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, 0.0f), QVector3D(x2 - x4, y2 - y4, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x4, y4, z+zHeight), n);
    add(QVector3D(x1, y1, z+zHeight), n);
    add(QVector3D(x2, y2, z+zHeight), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, z+zHeight), n);
    add(QVector3D(x3, y3, z+zHeight), n);
    add(QVector3D(x4, y4, z+zHeight), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

//Draw extrudes to define a 3D rectangle with z defined as the center of the rectangles height and output the vertex information into a stl file in the correct format
void Draw3D::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat extrudeThickness)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f)); //QVector3D(0.0f, 0.0f, -0.1f) ???

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, +extrudeThickness), n);
    add(QVector3D(x1, y1, -extrudeThickness), n);
    add(QVector3D(x2, y2, +extrudeThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, -extrudeThickness), n);
    add(QVector3D(x2, y2, +extrudeThickness), n);
    add(QVector3D(x1, y1, -extrudeThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

//Draw extrudes to define a 3D rectangle with z defined and output the vertex information into a stl file in the correct format
void Draw3D::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z, GLfloat zHeight){
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, -0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";
    add(QVector3D(x1, y1, z+zHeight), n);
    add(QVector3D(x1, y1, z), n);
    add(QVector3D(x2, y2, z+zHeight), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, z), n);
    add(QVector3D(x2, y2, z+zHeight), n);
    add(QVector3D(x1, y1, z), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

// Draw a 3D rectangle defining x, y, length "x", width "y" and height "z" - z is defined as the origin z = 0 which is the center of the rectangle
void Draw3D::rectangle(GLfloat x, GLfloat y, GLfloat length, GLfloat width, GLfloat height){
    quad(x, y, x + length, y, x + length, y + width, x, y + width, height);
    extrude(x, y, x + length, y, height);
    extrude(x + length, y, x + length, y + width, height);
    extrude(x + length, y + width, x, y + width, height);
    extrude(x, y + width, x, y, height);
}
// Draw a 3D rectangle defining x, y, z, length "x", width "y" and height "z" - z height is defined as the positive direction from the z specified
void Draw3D::rectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height){
    quad(x, y, x + length, y, x + length, y + width, x, y + width, z, height);
    extrude(x, y, x + length, y, z, height);
    extrude(x + length, y, x + length, y + width, z, height);
    extrude(x + length, y + width, x, y + width, z, height);
    extrude(x, y + width, x, y, z, height);
}

