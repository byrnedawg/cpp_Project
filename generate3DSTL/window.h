#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QLabel>

class QSlider;
class QPushButton;

class GLWidget;
class MainWindow;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(MainWindow *mw);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private slots:


private:
    QSlider *createSlider();
    QSlider *createSlider2();

    GLWidget *glWidget;
    QSlider *xSlider;
    QSlider *ySlider;
    QSlider *zSlider;
    QSlider *viewSlider;

    QLabel *modelLabel;
    QLabel *xLabel;
    QLabel *yLabel;
    QLabel *zLabel;
    QLabel *viewLabel;

    MainWindow *mainWindow;
};

#endif
