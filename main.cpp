#include <QtGui/QApplication>
#include <QtCore>

#include "glwindow.h"
#include "pluginimpl.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PluginImpl plugin;
    QDir dir("plugins", "*.so *.dll", QDir::Name, QDir::Files | QDir::Readable);
    QStringList libs = dir.entryList();

    foreach(QString fileName, libs) {
        qDebug() << "Loading " << fileName;

        QLibrary binary(dir.filePath(fileName));
        if (!binary.load()) {
            qDebug("%s", qPrintable(binary.errorString()));
            continue;
        }

        EntryPointProto entryPoint = (EntryPointProto) binary.resolve("registerPlugin");
        if (entryPoint == 0) {
            qDebug() << "No entry point found";
            binary.unload();
            continue;
        }

        entryPoint(&plugin);
    }

    GLWindow window(&plugin);
    window.show();

    return app.exec();
}
