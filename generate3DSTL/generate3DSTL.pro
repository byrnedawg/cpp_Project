HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
    draw3d.h \
    rectangle.h \
    shapes3d.h \
    tetrahedron3d.h \
    cylinder3d.h \
    pyramid3d.h \
    cone3d.h \
    triangle3d.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
    draw3d.cpp \
    rectangle.cpp \
    shapes3d.cpp \
    tetrahedron3d.cpp \
    cylinder3d.cpp \
    pyramid3d.cpp \
    cone3d.cpp \
    triangle3d.cpp

QT           += widgets

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
#INSTALLS += target
