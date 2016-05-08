#include "tcube.h"

Tcube::~Tcube()
{

}
Tcube::Tcube(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, GLfloat height, GLfloat rotation, int slice):
    //Cube2(p1,p2,p3,p4,p5,p6,p7,p8),x(x),y(y),z(z),length(length),width(width),height(height),rotation(rotation),slice(slice)
    Shapes3D(x,y,z),length(length),width(width),height(height),rotation(rotation),slice(slice)
{
    shape_data.resize(216*slice);//6 values * 6 vertex * 6 faces * slice
    this->draw();
}

void Tcube::draw()
{
   // orig(x,y,z);
    orig.setX(x);
    orig.setY(y);
    orig.setZ(z);
    p1=orig;
    GLfloat dia=qSqrt(length*length+width*width);
    GLfloat angleDia= atan(width/length);
   // p2(x+length,y,z);
    p2.setX(x+length);
    p2.setY(y);
    p2.setZ(z);

//    p3(x+length,y+width,z);
    p3.setX(x+length);
    p3.setY(y+width);
    p3.setZ(z);

   // p4(x,y+width,z);
    p4.setX(x);
    p4.setY(y+width);
    p4.setZ(z);

    GLfloat angle=rotation/slice;
    for(int i=0;i<slice;i++){
      p1.setX(x);
      p1.setY(y);
      p1.setZ(z);

      p2.setX(p1.x()+length*qCos(angle*i));
      p2.setY(p1.y()+length*qSin(angle*i));
      p2.setZ(p1.z());

      p3.setX(p1.x()+dia*qCos(angleDia+angle*i));
      p3.setY(p1.y()+dia*qSin(angleDia+angle*i));
      p3.setZ(p1.z());

      p4.setX(p1.x()+width*qCos(M_PI/2+angle*i));
      p4.setY(p1.x()+width*qSin(M_PI/2+angle*i));
      p4.setZ(p1.z());


      p5.setX(p1.x());
      p5.setY(p1.y());
      p5.setZ(p1.z()+height/slice);

      p6.setX(p5.x()+length*qCos(angle*i));
      p6.setY(p5.y()+length*qSin(angle*i));
      p6.setZ(p5.z());


      p7.setX(p5.x()+dia*qCos(angleDia+angle*i));
      p7.setY(p5.y()+dia*qSin(angleDia+angle*i));
      p7.setZ(p5.z());


      p8.setX(p5.x()+width*qCos(M_PI/2+angle*i));
      p8.setY(p5.x()+width*qSin(M_PI/2+angle*i));
      p8.setZ(p5.z());
      /*
      cout<< "p1 ("<<p1.x()<<" "<<p1.y()<<" "<<p1.z()<<")\n";
      cout<< "p2 ("<<p2.x()<<" "<<p2.y()<<" "<<p2.z()<<")\n";
      cout<< "p3 ("<<p3.x()<<" "<<p3.y()<<" "<<p3.z()<<")\n";
      cout<< "p4 ("<<p4.x()<<" "<<p4.y()<<" "<<p4.z()<<")\n";
      cout<< "p5 ("<<p5.x()<<" "<<p5.y()<<" "<<p5.z()<<")\n";
      cout<< "p6 ("<<p6.x()<<" "<<p6.y()<<" "<<p6.z()<<")\n";
      cout<< "p7 ("<<p7.x()<<" "<<p7.y()<<" "<<p7.z()<<")\n";
      cout<< "p8 ("<<p8.x()<<" "<<p8.y()<<" "<<p8.z()<<")\n";
      cout<<"***************************************\n";
      //system("pause");
*/

  //  Cube2(p1,p2,p3,p4,p5,p6,p7,p8);
  //  Cube2::draw();
      face((GLfloat)p1.x(),(GLfloat)p1.y(),(GLfloat)p1.z(),(GLfloat)p4.x(),(GLfloat)p4.y(),(GLfloat)p4.z(),(GLfloat)p3.x(),(GLfloat)p3.y(),(GLfloat)p3.z(),(GLfloat)p2.x(),(GLfloat)p2.y(),(GLfloat)p2.z());   //bottom
      face((GLfloat)p5.x(),(GLfloat)p5.y(),(GLfloat)p5.z(),(GLfloat)p6.x(),(GLfloat)p6.y(),(GLfloat)p6.z(),(GLfloat)p7.x(),(GLfloat)p7.y(),(GLfloat)p7.z(),(GLfloat)p8.x(),(GLfloat)p8.y(),(GLfloat)p8.z()); // top
      face((GLfloat)p1.x(),(GLfloat)p1.y(),(GLfloat)p1.z(),(GLfloat)p2.x(),(GLfloat)p2.y(),(GLfloat)p2.z(),(GLfloat)p6.x(),(GLfloat)p6.y(),(GLfloat)p6.z(),(GLfloat)p5.x(),(GLfloat)p5.y(),(GLfloat)p5.z()); // width side
      face((GLfloat)p2.x(),(GLfloat)p2.y(),(GLfloat)p2.z(),(GLfloat)p3.x(),(GLfloat)p3.y(),(GLfloat)p3.z(),(GLfloat)p7.x(),(GLfloat)p7.y(),(GLfloat)p7.z(),(GLfloat)p6.x(),(GLfloat)p6.y(),(GLfloat)p6.z()); // width side
      face((GLfloat)p3.x(),(GLfloat)p3.y(),(GLfloat)p3.z(),(GLfloat)p4.x(),(GLfloat)p4.y(),(GLfloat)p4.z(),(GLfloat)p8.x(),(GLfloat)p8.y(),(GLfloat)p8.z(),(GLfloat)p7.x(),(GLfloat)p7.y(),(GLfloat)p7.z()); // length side
      face((GLfloat)p1.x(),(GLfloat)p1.y(),(GLfloat)p1.z(),(GLfloat)p5.x(),(GLfloat)p5.y(),(GLfloat)p5.z(),(GLfloat)p8.x(),(GLfloat)p8.y(),(GLfloat)p8.z(),(GLfloat)p4.x(),(GLfloat)p4.y(),(GLfloat)p4.z()); // length side

      x=p5.x();
      y=p5.y();
      z=p5.z();
    }
}
