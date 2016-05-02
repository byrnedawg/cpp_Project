HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
    draw3d.h \
    shapes3d.h \
    tetrahedron3d.h \
    cylinder3d.h \
    pyramid3d.h \
    cone3d.h \
    triangle3d.h \
    rectangle3D.h \
    sphere3d.h \
    iconosphere3d.h \
    cube2.h \
    tcube.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
    draw3d.cpp \
    shapes3d.cpp \
    tetrahedron3d.cpp \
    cylinder3d.cpp \
    pyramid3d.cpp \
    cone3d.cpp \
    triangle3d.cpp \
    rectangle3D.cpp \
    sphere3d.cpp \
    iconosphere3d.cpp \
    cube2.cpp \
    tcube.cpp

QT           += widgets

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
#INSTALLS += target
