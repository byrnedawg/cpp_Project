#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "draw3d.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setView(int distance);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
    void viewDistanceChanged(int distance);

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void setupVertexAttribs();

    bool my_core;
    int my_xRot;
    int my_yRot;
    int my_zRot;
    int my_viewDis;
    QPoint my_lastPos;
    Draw3D my_model3D;
    QOpenGLVertexArrayObject my_vao;
    QOpenGLBuffer my_model3DVbo;
    QOpenGLShaderProgram *my_program;
    int my_projMatrixLoc;
    int my_mvMatrixLoc;
    int my_normalMatrixLoc;
    int my_lightPosLoc;
    QMatrix4x4 my_proj;
    QMatrix4x4 my_camera;
    QMatrix4x4 my_world;
    bool my_transparent;
};

#endif
