#include "draw3d.h"
#include <qmath.h>


Draw3D::Draw3D()
    : m_count(0), vectorSize(1)
{
    //m_data.resize(2500 * 6); //allocate space for data
    //m_data.resize(100000 * 6); //allocate space for data
    m_data.resize(vectorSize); //Dynamically allocate space for data

    //Define 3D shapes to be drawn and outputed to stl file named model.stl
    //Draw Model below ................................................
    stlWriter.open ("modelRect.stl"); //name of stl file
    stlWriter << "solid model\n"; //first line of stl file

    //3D figures in stl file and 3D model space

     // rectangle(-7.0f, 7.0f, 0.0f, 7.0f, 5.0f, 2.5f); //rectangle x, y, z, length, width, height - works
     // extrudedRectangle(-3.0f, -3.0f, 0.0f, 6.0f, 6.0f, 4.0f, 0.5f); //extrudedRectangle x, y, z, length, width, height, thickness - works
     // cylinder(8.0f, -8.0f,-2.0f,3.0f,3.0f,8); //cylinder x, y, z, radius, height, NumSectors - 8 creates octagon
    //  cylinder(-9.0f, -9.0f,-2.0f,2.5f,3.0f,100); //cylinder x, y, z, radius, height, NumSectors
    // extrudedCylinder(0.0f, 0.0f, -4.0f, 1.0f , 2.5f, 8.0f,100); //extrudedCylinder x, y, z, inRadius, outRadius height, NumSectors
    // pyramid(8.0f, 8.0f, 1.0f, 4.0f, 4.0f, 5.0f); //pyramid x, y, z, length, width, height - works
    // pyramid(8.0f, 8.0f, 0.0f, 4.0f, 4.0f, -5.0f);//pyramid negative height flips over the pyramid
     // cone(5.0f, -5.0f, 2.0f,3.0f,9.0f,100, true); //Draw a cone with x,y,z, radius, height,numSides, cap - cover open end of cone T or F
     // tetrahedron(7.0f,0.0f, 0.0, 0.0, 7.0f, 0, 7.0f, 7.0f, 0, 7.0f); //Draw tetrahedron 3 x,y,z points and height of centroid z
      //tetrahedron(-7.0f,0.0f, 0, 0, -7.0f, 0, -7.0f, -7.0f, 0, 7.0f); //Draw tetrahedron 3 x,y,z points and height of centroid z - works

    // sphere2(1,1,-0.5,5,30); // x, y, z, radius, NumSectors
    Rectangle3D a(-7.0f, 7.0f, 0.0f, 7.0f, 5.0f, 2.5f); //rectangle x, y, z, length, width, height - works
    Rectangle3D b(7.0f, 7.0f, 0.0f, 7.0f, 5.0f, 2.5f);
    Rectangle3D c(7.0f, -7.0f, 0.0f, 7.0f, 5.0f, 2.5f);
    Rectangle3D d(-7.0f, -7.0f, 0.0f, 7.0f, 5.0f, 2.5f);

    Tetrahedron3D e(7.0f,0.0f, 0.0, 0.0, 7.0f, 0, 7.0f, 7.0f, 0, 7.0f); //Draw tetrahedron 3 x,y,z points and height of centroid z
    Tetrahedron3D f(-7.0f,0.0f, 0, 0, -7.0f, 0, -7.0f, -7.0f, 0, 7.0f); //Draw tetrahedron 3 x,y,z points and height of centroid z - works

    Cylinder3D g(8.0f, -8.0f,-2.0f,3.0f,3.0f,8); //cylinder x, y, z, radius, height, NumSectors - 8 creates octagon
    Cylinder3D h(-9.0f, -9.0f,-2.0f,2.5f,3.0f,100); //cylinder x, y, z, radius, height, NumSectors

    Cylinder3D i(0.0f, 0.0f, -4.0f, 1.0f , 2.5f, 8.0f,100); //extrudedCylinder x, y, z, inRadius, outRadius height, NumSectors

    Pyramid3D j(8.0f, 8.0f, 1.0f, 4.0f, 4.0f, 5.0f); //pyramid x, y, z, length, width, height - works
    Pyramid3D k(8.0f, 8.0f, 0.0f, 4.0f, 4.0f, -5.0f);//pyramid negative height flips over the pyramid

    Cone3D l(5.0f, -5.0f, 2.0f,3.0f,9.0f,100, true); //Draw a cone with x,y,z, radius, height,numSides, cap - cover open end of cone T or F

    Triangle3D q(-11.0f, 0.0f, 0.0f, 7.0f, 5.0f, 2.5f); //triangle x, y, z, length, width, height - works

    Rectangle3D r(-3.0f, -3.0f, 0.0f, 6.0f, 6.0f, 4.0f, 0.5f);

    Sphere3D s(15.0f,15.0f,15.0f,5.0f,20); // x, y, z, radius, NumSectors

    Iconosphere3D t(-15.0f, -15.0f, 0.0f,5.0f, 1); // x, y, z, radius, NumSectors

  //  Rectangle3D aa(-3.0f, 2.0f, -1.0f, 5.0f, 5.0f, 5.0f); //rectangle x, y, z, length, width, height - works

    print3D(a);
    print3D(e);
    print3D(f);
    print3D(g);
    print3D(h);
    print3D(i);
    print3D(j);
    print3D(k);
    print3D(l);
    print3D(q);
    print3D(r);
    //print3D(s);
    print3D(t);

    //Done with 3D model
    stlWriter << "endsolid model\n"; //last line of stl file
    stlWriter.close(); // close stl file


    //Done drawing model .....................................................


}
//void Draw3D::print3D(RectangleOBJ& a)
void Draw3D::print3D(Shapes3D& a)
{
   vectorSize += a.shape_data.size();
   m_data.resize(vectorSize);
   GLfloat *p = m_data.data() + m_count;
   int index = 0;
   GLfloat x, y, z, nx, ny, nz;
   for(QVector<GLfloat>::iterator i = a.shape_data.begin(); i != a.shape_data.end(); i++){
       *p++ = *i;
       if(index == 0){
           x = *i;
       }
       else if(index == 1 ){
           y = *i;
       }
       else if(index == 2 ){
           z = *i;
       }
       else if(index == 3){
           nx = *i;
       }
       else if(index == 4){
           ny = *i;
       }
       else if(index == 5){
           nz = *i;
           stlWriter << "facet normal " << nx << " " << ny << " " << nz << "\n";
           stlWriter << "outer loop \n";
           stlWriter << "vertex " << x << " " << y << " " << z <<"\n";
       }
       else if(index == 6 | index == 12){
           x = *i;
           stlWriter << "vertex " << x << " ";
       }
       else if(index == 7 | index == 13){
           y = *i;
           stlWriter << y << " ";
       }
       else if(index == 8 | index == 14){
           z = *i;
           stlWriter << z << "\n";
       }
       else{
           //do nothing ignore the other normal vectors
       }
       index++;
       if(index == 18){
            index = 0;
            stlWriter << "endloop\n";
            stlWriter << "endfacet\n";
       }
        m_count++;
   }
}

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

/************************************************************************************************************************/
/*Writed by Shaotu Jia*/
//quad2 is generated by two diagonal points (x1,y1,z1) and (x4,y4,z4). And it is the quad on spherical surface

void Draw3D::quad2(GLfloat x,GLfloat y,GLfloat z,GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x4,GLfloat y4,GLfloat z4,int NumSectors, GLfloat radius,GLfloat angle,GLfloat anglez){
    GLfloat alpha=2*M_PI/NumSectors;
    QVector3D n= QVector3D((x1+x4)/2-x,(y1+y4)/2-y,(z1+z4)/2-z);
   //QVector3D n = QVector3D::normal(QVector3D(radius*qCos(anglez+alpha*qCos(angle))+x - x1, radius*qCos(anglez+alpha)*qSin(angle)+y-y1, z4-z1), QVector3D(radius*qCos(angle+alpha)+x-x1, radius*qSin(angle+alpha)+y-y1, z1-z1));

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(radius*qCos(anglez+alpha)*qCos(angle)+x,radius*qCos(anglez+alpha)*qSin(angle)+y,z4),n);
    add(QVector3D(x4, y4, z4), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

    stlWriter << "facet normal " << n.x() << " " << n.y() << " " << n.z() << "\n";
    stlWriter << "outer loop \n";

    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(radius*qCos(angle+alpha)*qCos(anglez)+x, radius*qSin(angle+alpha)*qCos(anglez)+y, z1), n);
    add(QVector3D(x1, y1, z1), n);

    stlWriter << "endloop\n";
    stlWriter << "endfacet\n";

}
void Draw3D::sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, int NumSectors){

    for (int j=0; j<NumSectors;j++){
        GLfloat anglez=(j*M_PI)/(NumSectors*2);     //anglez is the angle between x-y plane and vector from origin to the point on spherical surface
                                                     //Range[0-90degree]
        GLfloat angle = (0 * 2 * M_PI) / NumSectors; //angle is the angle between x-axis and point which is on the spherical surface
        GLfloat angleSin = qSin(angle);
        GLfloat angleCos = qCos(angle);
        GLfloat x1 = radius * angleCos*qCos(anglez) + x;   //initialze (x1,y1,z1) and (x4,y4,z4)
        GLfloat y1 = radius * angleSin*qCos(anglez) + y;
        GLfloat z1 =radius * qSin(anglez)+z;
        GLfloat x4=0.0;
        GLfloat y4 = 0.0;
        GLfloat z4=0.0;
        GLfloat zn1=0.0;   //zn1 and zn4 are the reflection of coordinate of (x1,y1,z1) and (x4,y4,z4) based on x-y plane
        GLfloat zn4=0.0;

        for (int i=0; i < NumSectors; ++i) {

            angle = (i * 2 * M_PI) / NumSectors;

            x4 = radius * qCos(angle+2*M_PI/NumSectors)*qCos(anglez+2*M_PI/NumSectors) + x;
            y4 = radius * qSin(angle+2*M_PI/NumSectors)*qCos(anglez+2*M_PI/NumSectors) + y;
            z4 = radius * qSin(anglez+2*M_PI/NumSectors) + z;

            quad2(x,y,z,x1,y1,z1,x4,y4,z4,NumSectors,radius,angle,anglez);
            zn1=-z1+2*z;
            zn4=-z4+2*z;
            quad2(x,y,z,x1,y1,zn1,x4,y4,zn4,NumSectors,radius,angle,anglez);  //draw the reflection hemi-sphere based on x-y plane
            x1=radius*qCos(angle+2*M_PI/NumSectors)*qCos(anglez)+x;
            y1=radius*qSin(angle+2*M_PI/NumSectors)*qCos(anglez)+y;
            z1=radius * qSin(anglez)+z;

            }
        x1 = x4;
        y1 = y4;
        z1 = z4;
        zn1=zn4;
    }

}



