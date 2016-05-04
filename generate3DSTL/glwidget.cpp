#include "glwidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      my_xRot(0),
      my_yRot(0),
      my_zRot(0),
      my_viewDis(-300),
      my_program(0)
{}

GLWidget::~GLWidget()
{
    cleanup();
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

// function called when sliders change value
void GLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != my_xRot) {
        my_xRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

// function called when sliders change value
void GLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != my_yRot) {
        my_yRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

// function called when sliders change value
void GLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != my_zRot) {
        my_zRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

// function called when sliders change value
void GLWidget::setView(int distance)
{
    if (distance != my_viewDis) {
        my_camera.setToIdentity();
        my_viewDis = distance;
        my_camera.translate(0, 0, my_viewDis/10.0f); //sets camera distance
        emit viewDistanceChanged(distance);
        update();
    }
}

void GLWidget::cleanup()
{
    makeCurrent();
    my_model3DVbo.destroy();
    delete my_program;
    my_program = 0;
    doneCurrent();
}

// QOpenGL configuration variables
static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

static const char *vertexShaderSource =
    "attribute vec4 vertex;\n"
    "attribute vec3 normal;\n"
    "varying vec3 vert;\n"
    "varying vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSource =
    "varying highp vec3 vert;\n"
    "varying highp vec3 vertNormal;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   gl_FragColor = vec4(col, 1.0);\n"
    "}\n";

// needed for drawing with GL
void GLWidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, my_transparent ? 0 : 1);

    my_program = new QOpenGLShaderProgram;
    my_program->addShaderFromSourceCode(QOpenGLShader::Vertex, my_core ? vertexShaderSourceCore : vertexShaderSource);
    my_program->addShaderFromSourceCode(QOpenGLShader::Fragment, my_core ? fragmentShaderSourceCore : fragmentShaderSource);
    my_program->bindAttributeLocation("vertex", 0);
    my_program->bindAttributeLocation("normal", 1);
    my_program->link();

    my_program->bind();
    my_projMatrixLoc = my_program->uniformLocation("projMatrix");
    my_mvMatrixLoc = my_program->uniformLocation("mvMatrix");
    my_normalMatrixLoc = my_program->uniformLocation("normalMatrix");
    my_lightPosLoc = my_program->uniformLocation("lightPos");

    //QOpenGL Vertex Object
    my_vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&my_vao);

    // Setup our vertex buffer object.
    my_model3DVbo.create();
    my_model3DVbo.bind();
    //allocate memory by looking at the Draw3D objects data
    my_model3DVbo.allocate(my_model3D.constData(), my_model3D.count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    my_camera.setToIdentity();
    my_camera.translate(0, 0, -300/10.0f); //sets camera distance

    // Light position is fixed.
    my_program->setUniformValue(my_lightPosLoc, QVector3D(0, 0, 70)); // sets lighting

    // releases active shader program
    my_program->release();
}

void GLWidget::setupVertexAttribs()
{
    my_model3DVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    my_model3DVbo.release();
}

void GLWidget::paintGL()
{
    // needed for gl functions
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //set original view for model
    my_world.setToIdentity();
    my_world.rotate(180.0f - (my_xRot / 16.0f), 1, 0, 0);
    my_world.rotate(my_yRot / 16.0f, 0, 1, 0);
    my_world.rotate(my_zRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&my_vao);
    my_program->bind();
    my_program->setUniformValue(my_projMatrixLoc, my_proj);
    my_program->setUniformValue(my_mvMatrixLoc, my_camera * my_world);
    QMatrix3x3 normalMatrix = my_world.normalMatrix();
    my_program->setUniformValue(my_normalMatrixLoc, normalMatrix);

    //Draw triangles based on Draw3D objects data
    glDrawArrays(GL_TRIANGLES, 0, my_model3D.vertexCount());


    my_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    my_proj.setToIdentity();
    my_proj.perspective(45.0f,GLfloat(w) / h, 0.01f, 300.0f); // max is 300
}

// function for moving the model with the mouse
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    my_lastPos = event->pos();
}

// function for moving the model with the mouse
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - my_lastPos.x();
    int dy = event->y() - my_lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(my_xRot + 8 * dy);
        setYRotation(my_yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(my_xRot + 8 * dy);
        setZRotation(my_zRot + 8 * dx);
    }
    my_lastPos = event->pos();
}
