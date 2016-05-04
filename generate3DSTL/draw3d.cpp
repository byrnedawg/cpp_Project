#include "draw3d.h"
#include <qmath.h>

Draw3D::Draw3D()
    : m_count(0), vectorSize(1)
{
    m_data.resize(vectorSize); //Dynamically allocate space for data

    //Define 3D shapes to be drawn and outputed to stl file named model.stl
    //Draw Model below ................................................
    stlWriter.open ("model3D.stl"); //name of stl file
    stlWriter << "solid model\n"; //first line of stl file



    /*

    Rectangle3D rectangle1(-7.0f, 7.0f, 10.0f, 7.0f, 5.0f, 2.5f); //rectangle x, y, z, length, width, height - works

    Tetrahedron3D tetrahedron1(7.0f,0.0f, 0.0, 0.0, 7.0f, 0, 7.0f, 7.0f, 0, 7.0f); //Draw tetrahedron 3 x,y,z points and height of centroid z
    Tetrahedron3D tetrahedron2(-7.0f,0.0f, 0, 0, -7.0f, 0, -7.0f, -7.0f, 0, 7.0f); //Draw tetrahedron 3 x,y,z points and height of centroid z - works

    Cylinder3D octagon1(8.0f, -8.0f,-2.0f,3.0f,3.0f,8); //cylinder x, y, z, radius, height, NumSectors - 8 creates octagon
    Cylinder3D cylinder1(-9.0f, -9.0f,-2.0f,2.5f,3.0f,100); //cylinder x, y, z, radius, height, NumSectors

    Cylinder3D exCylinder1(0.0f, 0.0f, -4.0f, 1.0f , 2.5f, 8.0f,100); //extrudedCylinder x, y, z, inRadius, outRadius height, NumSectors

    Pyramid3D pyramid1(8.0f, 8.0f, 1.0f, 4.0f, 4.0f, 5.0f); //pyramid x, y, z, length, width, height - works
    Pyramid3D pyramid2(8.0f, 8.0f, 0.0f, 4.0f, 4.0f, -5.0f);//pyramid negative height flips over the pyramid

    Cone3D cone1(5.0f, -5.0f, 2.0f,3.0f,9.0f,100, true); //Draw a cone with x,y,z, radius, height,numSides, cap - cover open end of cone T or F

    Triangle3D triangle1(-11.0f, 0.0f, 0.0f, 7.0f, 5.0f, 2.5f); //triangle x, y, z, length, width, height - works

    Rectangle3D exRectangle1(-3.0f, -3.0f, 0.0f, 6.0f, 6.0f, 4.0f, 0.5f); //Extruded rectangle x, y, z, length, width, height - works

    Iconosphere3D iconosphere1(-15.0f, -15.0f, 0.0f,5.0f, 1); // x, y, z, radius, NumSectors

    Cylinder3D cylinder2 (15,-15,0,5,10,M_PI/4,M_PI/4,30); //(center.x,center.y,center.z,radius,height,incline in x-drection,incline in y-direction,accurarcy)
   //  print3D(w);
    Cylinder3D cylinder3(30,30,10,10,0,5,10,M_PI*2,100); //(axis.x,axis.y,center.x,center.y,center.z,radius,height, rotation angle, accuarcy)


   print3D(rectangle1);
   print3D(tetrahedron1);
   print3D(tetrahedron2);
   print3D(octagon1);
   print3D(cylinder1);
   print3D(exCylinder1);
   print3D(pyramid1);
   print3D(pyramid2);
   print3D(cone1);
   print3D(triangle1);
   print3D(exRectangle1);
   print3D(iconosphere1);
   print3D(cylinder2);
   print3D(cylinder3);


    //3D figures in stl file and 3D model space
    closeSTLWriter();
    */
}

void Draw3D::closeSTLWriter(){
      stlWriter << "endsolid model\n"; //last line of stl file
      stlWriter.close(); // close stl file
      //Done drawing model and STL file
}

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
       else if((index == 6) | (index == 12)){
           x = *i;
           stlWriter << "vertex " << x << " ";
       }
       else if((index == 7) | (index == 13)){
           y = *i;
           stlWriter << y << " ";
       }
       else if((index == 8) | (index == 14)){
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


