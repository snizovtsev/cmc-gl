#include <QtGui/QApplication>
#include <GL/glut.h>
#include "glwindow.h"

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    QApplication app(argc, argv);
    GLWindow window;
    window.show();

    return app.exec();
}
