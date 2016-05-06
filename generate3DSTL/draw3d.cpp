#include "draw3d.h"
#include <qmath.h>
#include <QInputDialog>
#include <QtGui>
#include <QMessageBox>

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
       else if((index == 6) || (index == 12)){
           x = *i;
           stlWriter << "vertex " << x << " ";
       }
       else if((index == 7) || (index == 13)){
           y = *i;
           stlWriter << y << " ";
       }
       else if((index == 8) || (index == 14)){
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

void Draw3D::promptUserInput()
{
    int answer = 0;
    GLfloat x = 0;
    GLfloat y = 0;
    GLfloat z = 0;
    GLfloat x2 = 0;
    GLfloat y2 = 0;
    GLfloat z2 = 0;
    GLfloat x3 = 0;
    GLfloat y3 = 0;
    GLfloat z3 = 0;
    GLfloat length = 0;
    GLfloat width = 0;
    GLfloat height = 0;
    GLfloat thickness = 0;
    GLfloat radius = 0;
    GLfloat inRadius = 0;
    GLfloat outRadius = 0;
   // GLfloat rotation = 0;
    int NumSectors = 0;
    bool cap = true;

    QStringList items;
    items << "Rectangle" << "Extruded Rectangle" << "Cylinder" << "Extruded Cylinder" << "Cone" << "Iconosphere" << "Pyramid"
          << "Tetrahedron" << "Triangle" << "Sphere" ;


    do {
        bool ok;
        QString item = QInputDialog::getItem(0,"Shape to add", "Shapes:", items, 0, false, &ok);
        if (ok && (!item.compare("Rectangle")))
        {
            x = QInputDialog::getDouble(0, "add Rectangle", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Rectangle", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Rectangle", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    length = QInputDialog::getDouble(0, "add Rectangle", "Length:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    width = QInputDialog::getDouble(0, "add Rectangle", "Width:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Rectangle", "Height:", 1.0, -30, 30, 2, &ok);
            if(ok){
                Rectangle3D rectangle(x,y,z, length, width, height);
                print3D(rectangle);
            }
        }
        else if(ok && (!item.compare("Extruded Rectangle")))
        {
            x = QInputDialog::getDouble(0, "add Extruded Rectangle", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Extruded Rectangle", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Extruded Rectangle", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    length = QInputDialog::getDouble(0, "add Extruded Rectangle", "Length:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    width = QInputDialog::getDouble(0, "add Extruded Rectangle", "Width:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Extruded Rectangle", "Height:", 1.0, -30, 30, 2, &ok);
            if(ok)
                    thickness = QInputDialog::getDouble(0, "add Extruded Rectangle", "Thickness:", 1.0, 0, 30, 2, &ok);
            if(ok){
                Rectangle3D exRectangle(x,y,z, length, width, height, thickness);
                print3D(exRectangle);
            }
        }
        else if(ok && (!item.compare("Cylinder")))
        {
            x = QInputDialog::getDouble(0, "add Cylinder", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Cylinder", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Cylinder", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    radius = QInputDialog::getDouble(0, "add Cylinder", "Radius:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Cylinder", "Height:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    NumSectors = QInputDialog::getInt(0, "add Cylinder", "NumSectors:", 100, 1, 100, 1, &ok);
            if(ok){
                Cylinder3D cylinder(x,y,z, radius, height, NumSectors);
                print3D(cylinder);
            }
        }
        else if(ok && (!item.compare("Extruded Cylinder")))
        {
            x = QInputDialog::getDouble(0, "add Extruded Cylinder", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Extruded Cylinder", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Extruded Cylinder", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    inRadius = QInputDialog::getDouble(0, "add Extruded Cylinder", "in Radius:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    outRadius = QInputDialog::getDouble(0, "add Extruded Cylinder", "out Radius:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Extruded Cylinder", "Height:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    NumSectors = QInputDialog::getInt(0, "add Extruded Cylinder", "NumSectors:", 100, 1, 100, 1, &ok);
            if(ok){
                Cylinder3D exCylinder(x,y,z, inRadius, outRadius, height, NumSectors);
                print3D(exCylinder);
            }
        }
        else if(ok && (!item.compare("Cone")))
        {
            x = QInputDialog::getDouble(0, "add Cone", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Cone", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Cone", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    radius = QInputDialog::getDouble(0, "add Cone", "Radius:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Cone", "Height:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    NumSectors = QInputDialog::getInt(0, "add Cone", "NumSectors:", 100, 1, 100, 1, &ok);
            if(ok)
                    cap = QInputDialog::getInt(0, "add Cone", "Cap:", 1, 0, 1, 1, &ok);
            if(ok){
                Cone3D cone(x,y,z, radius, height, NumSectors, cap);
                print3D(cone);
            }
        }
        else if(ok && (!item.compare("Iconosphere")))
        {
            x = QInputDialog::getDouble(0, "add Iconosphere", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Iconosphere", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Iconosphere", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    radius = QInputDialog::getDouble(0, "add Iconosphere", "Radius:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    NumSectors = QInputDialog::getInt(0, "add Iconosphere", "NumSectors:", 1, 1, 4, 1, &ok);
            if(ok){
                Iconosphere3D icon(x,y,z, radius, NumSectors);
                print3D(icon);
            }
        }

        else if(ok && (!item.compare("Pyramid")))
        {
            x = QInputDialog::getDouble(0, "add Pyramid", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Pyramid", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Pyramid", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    length = QInputDialog::getDouble(0, "add Pyramid", "Length:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    width = QInputDialog::getDouble(0, "add Pyramid", "Width:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Pyramid", "Height:", 1.0, -30, 30, 2, &ok);
            if(ok){
                Pyramid3D pyramid(x,y,z, length, width, height);
                print3D(pyramid);
            }
        }

        else if(ok && (!item.compare("Tetrahedron")))
        {
            x = QInputDialog::getDouble(0, "add Tetrahedron", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Tetrahedron", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                z = QInputDialog::getDouble(0, "add Tetrahedron", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                x2 = QInputDialog::getDouble(0, "add Tetrahedron", "X2:", 1.0, -30, 30, 2, &ok);
            if(ok)
                y2 = QInputDialog::getDouble(0, "add Tetrahedron", "Y2:", 1.0, -30, 30, 2, &ok);
            if(ok)
                z2 = QInputDialog::getDouble(0, "add Tetrahedron", "Z2:", 1.0, -30, 30, 2, &ok);
            if(ok)
                x3 = QInputDialog::getDouble(0, "add Tetrahedron", "X3:", 1.0, -30, 30, 2, &ok);
            if(ok)
                y3 = QInputDialog::getDouble(0, "add Tetrahedron", "Y3:", 1.0, -30, 30, 2, &ok);
            if(ok)
                z3 = QInputDialog::getDouble(0, "add Tetrahedron", "Z3:", 1.0, -30, 30, 2, &ok);
            if(ok)
                height = QInputDialog::getDouble(0, "add Tetrahedron", "Height:", 1.0, 0.01, 30, 2, &ok);
            if(ok){
                Tetrahedron3D tetrahedron(x, y, z, x2, y2, z2, x3, y3, z3, height);
                print3D(tetrahedron);
            }
        }

        else if(ok && (!item.compare("Triangle")))
        {
            x = QInputDialog::getDouble(0, "add Triangle", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Triangle", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Triangle", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    length = QInputDialog::getDouble(0, "add Triangle", "Length:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    width = QInputDialog::getDouble(0, "add Triangle", "Width:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    height = QInputDialog::getDouble(0, "add Triangle", "Height:", 1.0, 0.01, 30, 2, &ok);
            if(ok){
                Triangle3D triangle(x,y,z, length, width, height);
                print3D(triangle);
            }
        }
        else
        {
            x = QInputDialog::getDouble(0, "add Sphere", "X:", 0.0, -30, 30, 2, &ok);
            if(ok)
                y = QInputDialog::getDouble(0, "add Sphere", "Y:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    z = QInputDialog::getDouble(0, "add Sphere", "Z:", 0.0, -30, 30, 2, &ok);
            if(ok)
                    radius = QInputDialog::getDouble(0, "add Sphere", "Radius:", 1.0, 0.01, 30, 2, &ok);
            if(ok)
                    NumSectors = QInputDialog::getInt(0, "add Sphere", "NumSectors:", 30, 10, 100, 1, &ok);
            if(ok){
                Sphere3D sphere(x,y,z, radius, NumSectors);
                print3D(sphere);
            }
        }

        QString response = QString("Want to add another shape to the model?");
        answer = QMessageBox::question(0, "Add Another Shape?", response, QMessageBox::Yes | QMessageBox::No);
    } while (answer == QMessageBox::Yes);

}



