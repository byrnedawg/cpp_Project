#include "draw3d.h"
#include <qmath.h>

Draw3D::Draw3D()
    : m_count(0)
{
    //m_data.resize(2500 * 6); //allocate space for data
    m_data.resize(15000 * 6); //allocate space for data

    //Define 3D shapes to be drawn and outputed to stl file named model.stl
    //Draw Model below ................................................
    stlWriter.open ("model.stl"); //name of stl file
    stlWriter << "solid model\n"; //first line of stl file

    //3D figures in stl file and 3D model space

      rectangle(-0.6f,0.6f, -0.4f, 0.3f, 0.5f, 0.25f); //rectangle x, y, z, length, width, height
      extrudedRectangle(-0.3f, -0.3f, -0.0f, 0.6f, 0.6f, 0.4f, 0.05f); //extrudedRectangle x, y, z, length, width, height, thickness
      cylinder(0.8f, -0.8f,-0.2f,0.3f,0.3f,8); //cylinder x, y, z, radius, height, NumSectors - 8 creates octagon
      cylinder(-0.9f, -0.9f,-0.2f,0.25f,0.3f,100); //cylinder x, y, z, radius, height, NumSectors
      extrudedCylinder(0.0f, 0.0f, -0.4f, 0.1f ,0.25f,0.8f,100); //extrudedCylinder x, y, z, inRadius, outRadius height, NumSectors
      pyramid(0.8f, 0.8f, 0.1f, 0.4f, 0.4f, 0.5f); //pyramid x, y, z, length, width, height
      pyramid(0.8f, 0.8f, 0.0f, 0.4f, 0.4f, -0.5f);//pyramid negative height flips over the pyramid
      cone(0.5f, -0.5f,0.2f,0.3f,0.9f,100,false); //Draw a cone with x,y,z, radius, height,numSides, cap - cover open end of cone T or F
      tetrahedron(0.7f,0.0f, 0, 0, .7, 0, 0.7f, 0.7f, 0, 0.7f); //Draw tetrahedron 3 x,y,z points and height of centroid z
      tetrahedron(-0.7f,0.0f, 0, 0, -.7, 0, -0.7f, -0.7f, 0, 0.7f); //Draw tetrahedron 3 x,y,z points and height of centroid z

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

void Draw3D::tri(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3){
    QVector3D n = QVector3D::normal(QVector3D(x3 - x1, y3 - y1, z3 - z1), QVector3D(x2 - x1, y2 - y1, z2 - z1));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x2, y2, z2), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

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
void Draw3D::quad(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4){
    QVector3D n = QVector3D::normal(QVector3D(x4 - x1, y4 - y1, z4 - z1), QVector3D(x2 - x1, y2 - y1, z2 - z1));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x2, y2, z2), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x4, y4, z4), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    n = QVector3D::normal(QVector3D(x1 - x4, y1 - y4, z1 - z4), QVector3D(x2 - x4, y2 - y4, z2 - z4));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

//Draw extrudes to define a 3D rectangle with z defined as the center of the rectangles height and output the vertex information into a stl file in the correct format
void Draw3D::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat extrudeThickness)
{
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, 0.0f), QVector3D(x2 - x1, y2 - y1, 0.0f)); //QVector3D(0.0f, 0.0f, -0.1f) ???


    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, extrudeThickness), n);
    add(QVector3D(x1, y1, -extrudeThickness), n);
    add(QVector3D(x2, y2, extrudeThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x2, y2, -extrudeThickness), n);
    add(QVector3D(x2, y2, extrudeThickness), n);
    add(QVector3D(x1, y1, -extrudeThickness), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

//Draw extrudes to define a 3D rectangle with z defined and output the vertex information into a stl file in the correct format
void Draw3D::extrude(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat z, GLfloat zHeight){
    QVector3D n = QVector3D::normal(QVector3D(0.0f, 0.0f, z - z+zHeight), QVector3D(x2 - x1, y2 - y1, 0));

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
// Draw tetrahedron 3 x,y,z points and height of centroid z
void Draw3D::tetrahedron(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3, GLfloat height){
    GLfloat x4 = (x1+x2+x3)/3; //find centroid x
    GLfloat y4 = (y1+y2+y3)/3; //find centroid y
    GLfloat z4 = height; //find centroid z
    tri(x1, y1, z1, x3, y3, z3, x2, y2, z2); //right hand rule with to find correct normals
    tri(x4, y4, z4, x3, y3, z3, x1, y1, z1);
    tri(x4, y4, z4, x1, y1, z1, x2, y2, z2);
    tri(x4, y4, z4, x2, y2, z2, x3, y3, z3);
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
   // quad(x, y, x + length, y, x + length, y + width, x, y + width, z, height);
    quad(x, y, z, x, y + width, z, x + length, y + width, z, x+ length, y, z);
    quad(x,y,height, x + length, y, height, x + length, y + width, height, x, y+width, height);
    quad(x,y,z,x + length, y, z, x + length, y, height, x, y, height);
    quad(x + length, y + width, z, x, y+ width, z, x, y +width, height, x + length, y + width, height);
    quad(x, y + width, z, x, y, z, x, y, height, x, y + width, height);
    quad(x + length, y, z, x + length, y + width, z, x + length, y + width, height, x + length, y, height);

    /*
    quad(x, y, x + length, y, x + length, y + width, x, y + width, z, height);
    extrude(x, y, x + length, y, z, height);
    extrude(x + length, y, x + length, y + width, z, height);
    extrude(x + length, y + width, x, y + width, z, height);
    extrude(x, y + width, x, y, z, height);
    */
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

        quad(x4,y4,z, x3, y3, z, x2, y2, z, x1, y1, z); // bottom
        quad(x1,y1,height, x2, y2, height, x3, y3, height, x4, y4, height); // top

        quad(x1,y1,z, x1, y1,height, x4, y4, height, x4, y4, z); // cylinder sides

        //quad(x1, y1, x2, y2, x3, y3, x4, y4, z, height);
       // extrude(x2, y2, x3, y3, z, height);
        //extrude(x4, y4, x1, y1, z, height);
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


        quad(x4,y4,z, x3, y3, z, x2, y2, z, x1, y1, z); // bottom
        quad(x1,y1,height, x2, y2, height, x3, y3, height, x4, y4, height); // top

        quad(x1,y1,z, x1, y1,height, x4, y4, height, x4, y4, z); // cylinder sides

        quad(x3,y3,z, x3, y3,height, x2, y2, height, x2, y2, z); // inner sides

        //quad(x1, y1, x2, y2, x3, y3, x4, y4, z, height);
        //extrude(x2, y2, x3, y3, z, height);
       // extrude(x4, y4, x1, y1, z,  height);
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

    if(height < 0){
         n = QVector3D::normal(QVector3D(x2 - x1, y2 - y1, 0.0f), QVector3D(x4 - x1, y4 - y1, 0.0f));

        stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
        stlWriter << "outer loop \n";

        add(QVector3D(x1, y1, z), n);
        add(QVector3D(x2, y2, z), n);
        add(QVector3D(x4, y4, z), n);

        stlWriter << "endloop\n";
        stlWriter << "endfacet\n";

        stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
        stlWriter << "outer loop \n";

        add(QVector3D(x3, y3, z), n);
        add(QVector3D(x4, y4, z), n);
        add(QVector3D(x2, y2, z), n);

        stlWriter << "endloop\n";
        stlWriter << "endfacet\n";
    }else{
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
    }

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x2 - x5, y2 - y5, z - z5), QVector3D(x1 - x5, y1 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x1 - x5, y1 - y5, z - z5), QVector3D(x2 - x5, y2 - y5, z - z5));
    }
    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x2, y2, z ), n);
        add(QVector3D(x1, y1, z), n);

    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x1, y1, z), n);
        add(QVector3D(x2, y2, z ), n);
    }

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x3 - x5, y3 - y5, z - z5), QVector3D(x2 - x5, y2 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x2 - x5, y2 - y5, z - z5), QVector3D(x3 - x5, y3 - y5, z - z5));
    }

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x3, y3, z ), n);
        add(QVector3D(x2, y2, z), n);
    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x2, y2, z), n);
        add(QVector3D(x3, y3, z ), n);
    }

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x4 - x5, y4 - y5, z - z5), QVector3D(x3 - x5, y3 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x3 - x5, y3 - y5, z - z5), QVector3D(x4 - x5, y4 - y5, z - z5));
    }

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x4, y4, z ), n);
        add(QVector3D(x3, y3, z), n);
    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x3, y3, z), n);
        add(QVector3D(x4, y4, z ), n);
    }

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    if(height < 0.0f){
        n = QVector3D::normal(QVector3D(x1 - x5, y1 - y5, z - z5), QVector3D(x4 - x5, y4 - y5, z - z5));
    }else{
        n = QVector3D::normal(QVector3D(x4 - x5, y4 - y5, z - z5), QVector3D(x1 - x5, y1 - y5, z - z5));
    }

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    if(height < 0.0f){
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x1, y1, z ), n);
        add(QVector3D(x4, y4, z), n);
    }else{
        add(QVector3D(x5, y5, z5), n);
        add(QVector3D(x4, y4, z), n);
        add(QVector3D(x1, y1, z ), n);
    }

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";
}

// Draw a 3D cone defining x,y,z, radius, height,numSides, cap - cover open end of cone T or F
void Draw3D::cone(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat height, int NumSectors, bool cap){

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

        if(cap){
            quad(x1,y1,height, x2, y2, height, x3, y3, height, x4, y4, height); // bottom
        }
       // quad(x1,y1,height, x2, y2, z, x3, y3, z, x4, y4, height); // inner cone
        quad(x4,y4,height, x3, y3, z, x2, y2, z, x1, y1, height); // outer cone

       // quad(x1,y1,z, x2, y2, z, x3, y3, height, x4, y4, height); // blades
       // quad(x1,y1,z, x2, y2, height, x3, y3, height, x4, y4, z); // cone

        //quad(x1, y1, x2, y2, x3, y3, x4, y4, z, height);
        //extrude(x2, y2, x3, y3, z, height);
        //extrude(x4, y4, x1, y1, z, height);
    }
}



