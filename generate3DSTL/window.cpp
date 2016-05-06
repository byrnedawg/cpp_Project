#include "glwidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QMainWindow>

Window::Window(MainWindow *mw): mainWindow(mw){

    glWidget = new GLWidget;

    //create sliders for x, y, z rotation and how close the view is to the origin 0,0,0
    xSlider = createSlider();
    ySlider = createSlider();
    zSlider = createSlider();
    //view slider has a different creation function
    viewSlider = createSlider2();

    xLabel = new QLabel(tr("X"));
    yLabel = new QLabel(tr("Y"));
    zLabel = new QLabel(tr("Z"));
    viewLabel = new QLabel(tr("Zoom"));
    modelLabel = new QLabel(tr("3D Model View"));
    btnRectangle = new QPushButton("Add Rectangle");



    //sync sliders with the function they govern in GLWidget
    connect(xSlider, &QSlider::valueChanged, glWidget, &GLWidget::setXRotation);
    connect(glWidget, &GLWidget::xRotationChanged, xSlider, &QSlider::setValue);
    connect(ySlider, &QSlider::valueChanged, glWidget, &GLWidget::setYRotation);
    connect(glWidget, &GLWidget::yRotationChanged, ySlider, &QSlider::setValue);
    connect(zSlider, &QSlider::valueChanged, glWidget, &GLWidget::setZRotation);
    connect(glWidget, &GLWidget::zRotationChanged, zSlider, &QSlider::setValue);

    connect(viewSlider, &QSlider::valueChanged, glWidget, &GLWidget::setView);
    connect(glWidget, &GLWidget::viewDistanceChanged, viewSlider, &QSlider::setValue);

    //connect(btnRectangle, SIGNAL(clicked()), glWidget, SLOT(addRectangle()));


    //lines up widgets vertially or horizontally deppending on which layout is used
    // container lines up left to right on the window
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;
    container->addWidget(glWidget);
    container->addWidget(xLabel);
    container->addWidget(xSlider);
    container->addWidget(yLabel);
    container->addWidget(ySlider);
    container->addWidget(zLabel);
    container->addWidget(zSlider);
    container->addWidget(viewLabel);
    container->addWidget(viewSlider);

    mainLayout->addWidget(modelLabel);

    //interface objects and widgets
    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    //mainLayout->addWidget(btnRectangle);

    setLayout(mainLayout);

    //intialize values for the sliders
    xSlider->setValue(15 * 16);
    ySlider->setValue(345 * 16);
    zSlider->setValue(0 * 16);
    viewSlider->setValue(-300);

    //name of the app window
    setWindowTitle(tr("Generate 3D Model + stl. Files"));
}

//create the rotation sliders about the x, y, and z axis
QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

//create the zoom in zoom out slider
QSlider *Window::createSlider2()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setValue(-300);
    slider->setMinimum(-2000);
    slider->setMaximum(-100);
    slider->setSingleStep(1);
    slider->setSliderPosition(-300);
    slider->setTickInterval(100);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

//close the application with the escape key
void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}

