HEADERS       = glwidget.h \
                window.h \
                mainwindow.h \
    draw3d.h \
    rectangle.h
SOURCES       = glwidget.cpp \
                main.cpp \
                window.cpp \
                mainwindow.cpp \
    draw3d.cpp \
    rectangle.cpp

QT           += widgets

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/opengl/hellogl2
#INSTALLS += target
