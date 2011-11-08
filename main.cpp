#include <QtGui/QApplication>
#include "glwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    GLWindow window;
    window.show();

    return app.exec();
}
