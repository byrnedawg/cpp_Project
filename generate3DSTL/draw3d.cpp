#include "draw3d.h"
#include <qmath.h>

Draw3D::Draw3D()
    : m_count(0)
{
    //m_data.resize(2500 * 6); //allocate space for data
    m_data.resize(10000 * 6); //allocate space for data

    //Define 3D shapes to be drawn and outputed to stl file named model.stl
    //Draw Model below ................................................
    stlWriter.open ("model.stl"); //name of stl file
    stlWriter << "solid model\n"; //first line of stl file

    //3D figures in stl file and 3D model space

  //  rectangle(0,0,-0.1f,0.4f,0.25f,0.2f); //rectangle x, y, z, length, width, height
  //  rectangle(0,0,0.1f,0.2f,0.2f,0.3f); //rectangle x, y, z, length, width, height
  //  rectangle(0,.2f, -0.2f, 0.2f, 0.5f, .07f);
    //rectangle(0, 0, -0.8, 0.2f, 0.2f, .5f);
    extrudedRectangle(-0.3f, -0.3f, -0.0f, 0.6f, 0.6f, 0.4f, 0.05f); //extrudedRectangle x, y, z, length, width, height, thickness
   // cylinder(-0.5f, -0.5f,-0.2f,0.3f,0.3f,100); //cylinder x, y, z, radius, height, NumSectors
    //cylinder(0.0f, 0.0, -0.2f,0.2f,0.5f,100); //cylinder x, y, z, radius, height, NumSectors
    extrudedCylinder(0.0f, 0.0f, -0.4f, 0.1f ,0.25f,0.8f,100); //extrudedCylinder x, y, z, inRadius, outRadius height, NumSectors
  //  pyramid(0,0,0, 0.4f, 0.6f, 0.7f); //pyramid x, y, z, length, width, height

    pyramid(0.4f, 0.4f, 0.0f, 0.4f, 0.4f, 0.5f); //pyramid x, y, z, length, width, height
    pyramid(0.4f, 0.4f, 0.0f, 0.4f, 0.4f, -0.5f);//pyramid negative height flips over the pyramid

    //Done with 3D model
    stlWriter << "endsolid model\n"; //last line of stl file
    stlWriter.close(); // close stl file


    //Done drawing model .....................................................


}

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

// Draw a 3D cylinder defining x, y, z, radius, height, numSectos - which determines how smooth it looks
void Draw3D::cylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors){

    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        GLfloat x1 = radius * angleSin + x;
        GLfloat y1 = radius * angleCos + y;
        GLfloat x2 = 0 * angleSin + x;
        GLfloat y2 = 0 * angleCos + y;

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        GLfloat x3 = 0 * angleSin + x;
        GLfloat y3 = 0 * angleCos + y;
        GLfloat x4 = radius * angleSin + x;
        GLfloat y4 = radius * angleCos + y;

        quad(x1, y1, x2, y2, x3, y3, x4, y4, z, height);

        extrude(x2, y2, x3, y3, z, height);
        extrude(x4, y4, x1, y1, z,  height);
    }
}

// Draw a 3D extrudedCylinder defining x, y, z, inRadius, outRadius, height, numSectos - which determines how smooth it looks
// Creates a pipe like cylinder where the inner radius is extruded out
void Draw3D::extrudedCylinder(GLfloat x, GLfloat y, GLfloat z, GLfloat inRadius, GLfloat outRadius, GLfloat height, int NumSectors){

    for (int i = 0; i < NumSectors; ++i) {
        GLfloat angle = (i * 2 * M_PI) / NumSectors;
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        GLfloat x1 = outRadius * angleSin + x;
        GLfloat y1 = outRadius * angleCos + y;
        GLfloat x2 = inRadius * angleSin + x;
        GLfloat y2 = inRadius * angleCos + y;

        angle = ((i + 1) * 2 * M_PI) / NumSectors;
        angleSin = qSin(angle);
        angleCos = qCos(angle);
        GLfloat x3 = inRadius * angleSin + x;
        GLfloat y3 = inRadius * angleCos + y;
        GLfloat x4 = outRadius * angleSin + x;
        GLfloat y4 = outRadius * angleCos + y;

        quad(x1, y1, x2, y2, x3, y3, x4, y4, z, height);

        extrude(x2, y2, x3, y3, z, height);
        extrude(x4, y4, x1, y1, z,  height);
    }
}

// Draw a 3D extrudedRectangle defining x, y, z, length, width, height, thickness - determines the wall thickness
// Creates a extruded rectangle where the inner rectangle is extruded out
void Draw3D::extrudedRectangle(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height, GLfloat thickness){
   rectangle(x, y, z, thickness, width, height);
   rectangle(x + thickness, y, z, length - thickness, thickness, height);
   rectangle(x + length - thickness, y, z, thickness, width, height);
   rectangle(x + thickness, y + width - thickness, z, length - thickness, thickness, height);
}

// Draw a 3D pyramid defining x, y, z, length, width, height
// Creates a 3D pyramid with the top point at the center of the length and width and at the point of the height
void Draw3D::pyramid(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height){

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

    n = QVector3D::normal(QVector3D(x5 - x1, y5 - y1, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, z), n);
    add(QVector3D(x2, y2, z ), n);
    add(QVector3D(x5, y5, z5), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    n = QVector3D::normal(QVector3D(x5 - x2, y5 - y2, 0.0f), QVector3D(x3 - x2, y3 - y2, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, z), n);
    add(QVector3D(x3, y3, z ), n);
    add(QVector3D(x5, y5, z5), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    n = QVector3D::normal(QVector3D(x5 - x3, y5 - y3, 0.0f), QVector3D(x4 - x3, y4 - y3, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x3, y3, z), n);
    add(QVector3D(x4, y4, z ), n);
    add(QVector3D(x5, y5, z5), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    n = QVector3D::normal(QVector3D(x5 - x4, y5 - y4, 0.0f), QVector3D(x1 - x4, y1 - y4, 0.0f));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x4, y4, z), n);
    add(QVector3D(x1, y1, z ), n);
    add(QVector3D(x5, y5, z5), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}



