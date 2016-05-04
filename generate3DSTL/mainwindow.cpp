#include "mainwindow.h"
#include "window.h"

MainWindow::MainWindow()
{
    setCentralWidget(new Window(this));
}


