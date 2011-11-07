#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QtGui>
#include <QGLWidget>
#include "objects.h"

class GLWindow : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWindow(QWidget *parent = 0);
    ~GLWindow();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void advance();

private:
    GLfloat xRot, yRot, zRot;
    GLfloat xVel, yVel, zVel;
    GLfloat zoom;

    QPoint lastPos;
    QTime  lastTime;

    Clock* clock;

    static void accumRotation(GLfloat &rot, GLfloat& vel);
    static void placeLight(GLfloat x, GLfloat y, GLfloat z);
};

#endif // GLWINDOW_H
