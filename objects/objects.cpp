#include <QTime>
#include <QVector4D>

#include "objects.h"

Plugin* plugin;

Arrows::Arrows()
    : ModelItem("raw:models/arrow.ply")
{
    stick = gluNewQuadric();
}

Arrows::~Arrows()
{
    gluDeleteQuadric(stick);
}

void Arrows::paint()
{
    plugin->setupMaterial(GL_FRONT_AND_BACK, BLACK_PLASTIC);

    QTime time = QTime::currentTime();
    glPushMatrix();
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, -0.04);
        glPushMatrix();
            glRotatef(360.0 / 60.0 * time.minute(), 0, 0, -1.0);
            plugin->getItem(modelFile)->paint();
        glPopMatrix();
        glPushMatrix();
            glRotatef(360.0 / 12.0 * (time.hour() % 12 + time.minute() / 60.0), 0, 0, -1.0);
            glScalef(1.0, 0.681, 1.0);
            glTranslatef(0.0, 0.0, -0.02);
            plugin->getItem(modelFile)->paint();
        glPopMatrix();
        glPushMatrix();
            glRotatef(360.0 / 60.0 * QTime::currentTime().second(), 0, 0, -1.0);
            glScalef(0.2, 1.0, 1.0);
            glTranslatef(0.0, 0.0, 0.02);
            plugin->getItem(modelFile)->paint();
        glPopMatrix();
    glPopMatrix();

    plugin->setupMaterial(GL_FRONT, SILVER);
    glPushMatrix();
        glTranslatef(0.0, 0.12, 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(stick, 0.02, 0.02, 0.15, 30, 30);
        glTranslatef(0.0, 0.0, 0.15);
        gluDisk(stick, 0.00, 0.02, 30, 30);
    glPopMatrix();
}

void Body::paint()
{
    plugin->setupMaterial(GL_FRONT_AND_BACK, GREEN_PLASTIC);
    glPushMatrix();
        glScalef(0.10, 0.10, 0.10);
        plugin->getItem(modelFile)->paint();
    glPopMatrix();
}

void Marks::paint()
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    plugin->setupMaterial(GL_FRONT, COPPER);
    plugin->setupMaterial(GL_BACK, BRONZE);
    glPushMatrix();
        glTranslatef(0.0f, 0.07f, 0.0f);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        plugin->getItem(modelFile)->paint();
    glPopMatrix();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
}

void Legs::paint()
{
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    plugin->setupMaterial(GL_FRONT_AND_BACK, SILVER);
    glPushMatrix();
        glTranslatef(-0.767, 0.5, 1.276);
        glScalef(0.10, 0.10, 0.10);
        plugin->getItem(modelFile)->paint();
    glPopMatrix();
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 0);
}

void Disk::paint()
{
    plugin->setupMaterial(GL_FRONT_AND_BACK, TURQUOISE);
    glPushMatrix();
        glScalef(0.10, 0.10, 0.10);
        plugin->getItem(modelFile)->paint();
    glPopMatrix();
}

void Clock::paint()
{
    plugin->getItem("item:body")->paint();
    plugin->getItem("item:legs")->paint();
    plugin->getItem("item:arrows")->paint();
    plugin->getItem("item:marks")->paint();
    plugin->getItem("item:disk")->paint();
}

void Clock::shadows()
{
    plugin->beginStencil("item:disk");
    plugin->paintShadow("item:arrows", QVector4D(0.0, -1.0, 0.0, 0.08));
    plugin->paintShadow("item:marks", QVector4D(0.0, -1.0, 0.0, 0.08));
    plugin->endStencil();

    plugin->beginStencil("item:marks");
    plugin->paintShadow("item:arrows", QVector4D(0.0, -1.0, 0.0, 0.06));
    plugin->endStencil();
}

void Table::paint()
{
    glEnable(GL_TEXTURE_2D);
    plugin->setupMaterial(GL_FRONT_AND_BACK, GOLD);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glPushMatrix();
    glTranslatef(0, 0, -8.85);
    plugin->getItem(modelFile)->paint();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void Scene::paint()
{
    plugin->getItem("item:table")->paint();
    plugin->getItem("item:clock")->paint();
}

void Scene::shadows()
{
    plugin->getItem("item:table")->shadows();
    plugin->getItem("item:clock")->shadows();
    plugin->beginStencil("item:table");
    plugin->paintShadow("item:clock", QVector4D(0, 0, 1.0, 1.35));
    plugin->endStencil();
}

extern "C" Q_DECL_EXPORT void registerPlugin(Plugin* _plugin)
{
    plugin = _plugin;

    plugin->registerItem(ArrowsFactory());
    plugin->registerItem(BodyFactory());
    plugin->registerItem(MarksFactory());
    plugin->registerItem(LegsFactory());
    plugin->registerItem(DiskFactory());
    plugin->registerItem(ClockFactory());
    plugin->registerItem(TableFactory());
    plugin->registerItem(SceneFactory());

    plugin->registerRootItem("item:scene");
}
