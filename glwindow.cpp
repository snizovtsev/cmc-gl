#include "glwindow.h"

#include <GL/glut.h>
#include <algorithm>
using namespace std;

GLWindow::GLWindow(QWidget *parent) :
    QGLWidget(parent),
    xRot(0.0), yRot(0.0), zRot(0.0),
    xVel(0.0), yVel(0.0), zVel(0.0),
    zoom(1.0)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(advance()));
    timer->start(50);
}

GLWindow::~GLWindow()
{
    delete scene;
}

void GLWindow::placeLight(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat lightpos[] = {x, y, z, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glDisable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 0.0);
    glTranslatef(x, y, z);
    GLUquadric *quad = gluNewQuadric();
    gluSphere(quad, 0.3, 100, 100);
    glTranslatef(-x, -y, -z);
    gluDeleteQuadric(quad);
    glEnable(GL_LIGHTING);
}

void GLWindow::initializeGL()
{
    glClearColor(.5f, .5f, .5f, 0.3f);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    // Turn on light
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_LIGHT0);

    // Load textures
    qDebug() << "Texture ID: " << bindTexture(QPixmap("models/tex.jpg"));

    scene = new Scene();
}

void GLWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(
            0.0, -8.0, 0.0,  /* Eye */
            0.0, 0.0, 0.0,  /* Center */
            0.0, 0.0, 1.0); /* Up */

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    glScalef(zoom, zoom, zoom);

    placeLight(1, -5, 3);

    scene->paint();
    scene->shadows();
}

void GLWindow::accumRotation(GLfloat &rot, GLfloat& vel)
{
    float sign = copysignf(1.0, vel);

    rot += vel;
    vel = copysignf(max(fabsf(vel) - 0.5f, 0.0f), sign);
}

void GLWindow::advance()
{
    accumRotation(xRot, xVel);
    accumRotation(yRot, yVel);
    accumRotation(zRot, zVel);

    updateGL();
}

void GLWindow::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(
            40.0, /* угол зрения в градусах */
            (GLfloat) w / h, /* коэффициент сжатия окна*/
            1, 100.0);  /* расстояние до плоскостей отсечения по глубине*/

    glMatrixMode (GL_MODELVIEW);
}

void GLWindow::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    lastTime.start();
}

void GLWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (lastTime.elapsed() <= 3)
        return;

    double dx = (event->x() - lastPos.x() + .0) / lastTime.elapsed() * 5;
    double dy = (event->y() - lastPos.y() + .0) / lastTime.elapsed() * 5;

    /* Set rotation velocity */
    if (event->buttons() & Qt::LeftButton) {
        xVel = dy;
        yVel = dx;
        zVel = 0.0;
        updateGL();
    } else if (event->buttons() & Qt::RightButton) {
        xVel = dy;
        yVel = 0.0;
        zVel = dx;
        updateGL();
    }

    lastPos = event->pos();
    lastTime.start();
}

void GLWindow::wheelEvent(QWheelEvent *event)
{
    zoom *= exp(event->delta() / 1000.0);
    updateGL();
}
