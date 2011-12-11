#include <QVector4D>

#include "cube.h"

Plugin* plugin;

Cube::Cube()
{
    sphere = gluNewQuadric();
}

Cube::~Cube()
{
    gluDeleteQuadric(sphere);
}

void Cube::paint()
{
    plugin->setupMaterial(GL_FRONT_AND_BACK, SILVER);
    glPushMatrix();
        glTranslatef(-2.0, -1.0, -0.3);
        gluSphere(sphere, 1.0, 100, 100);
    glPopMatrix();
}

void CubeScene::paint()
{
    plugin->getItem("item:cube")->paint();
}

void CubeScene::shadows()
{
}

extern "C" Q_DECL_EXPORT void registerPlugin(Plugin* _plugin)
{
    plugin = _plugin;

    plugin->registerItem(CubeFactory());
    plugin->registerItem(CubeSceneFactory());

    plugin->registerRootItem("item:cubeScene");
}
