#include "objects.h"
#include "materials.h"
#include <QTime>

void Arrows::paint()
{
    setupMaterial(GL_FRONT_AND_BACK, BLACK_PLASTIC);

    QTime time = QTime::currentTime();
    glPushMatrix();
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, -0.04);
        glPushMatrix();
            glRotatef(360.0 / 60.0 * time.minute(), 0, 0, -1.0);
            RawLoader::paint();
        glPopMatrix();
        glPushMatrix();
            glRotatef(360.0 / 12.0 * (time.hour() % 12 + time.minute() / 60.0), 0, 0, -1.0);
            glScalef(1.0, 0.681, 1.0);
            glTranslatef(0.0, 0.0, -0.02);
            RawLoader::paint();
        glPopMatrix();
        glPushMatrix();
            glRotatef(360.0 / 60.0 * QTime::currentTime().second(), 0, 0, -1.0);
            glScalef(0.2, 1.0, 1.0);
            glTranslatef(0.0, 0.0, 0.02);
            RawLoader::paint();
        glPopMatrix();
    glPopMatrix();

    setupMaterial(GL_FRONT, SILVER);
    GLUquadric* stick = gluNewQuadric();
    glPushMatrix();
        glTranslatef(0.0, 0.12, 0.0);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        gluCylinder(stick, 0.02, 0.02, 0.15, 30, 30);
        glTranslatef(0.0, 0.0, 0.15);
        gluDisk(stick, 0.00, 0.02, 30, 30);
    glPopMatrix();
    gluDeleteQuadric(stick);
}

void Body::paint()
{
    setupMaterial(GL_FRONT_AND_BACK, GREEN_PLASTIC);
    glPushMatrix();
        glScalef(0.10, 0.10, 0.10);
        RawLoader::paint();
    glPopMatrix();
}

void Marks::paint()
{
    setupMaterial(GL_FRONT, COPPER);
    setupMaterial(GL_BACK, BRONZE);
    glPushMatrix();
        glTranslatef(0.0f, 0.07f, 0.0f);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        RawLoader::paint();
    glPopMatrix();
}

void Legs::paint()
{
    setupMaterial(GL_FRONT_AND_BACK, SILVER);
    glPushMatrix();
        glTranslatef(-0.767, 0.5, 1.276);
        glScalef(0.10, 0.10, 0.10);
        RawLoader::paint();
    glPopMatrix();
}

void Disk::paint()
{
    setupMaterial(GL_FRONT_AND_BACK, TURQUOISE);
    glPushMatrix();
        glScalef(0.10, 0.10, 0.10);
        RawLoader::paint();
    glPopMatrix();
}

void Clock::paint()
{
    body.paint();
    legs.paint();
    arrows.paint();
    marks.paint();
    disk.paint();
}

void Clock::shadows()
{
    disk.beginStencil();
    arrows.paintShadow(QVector4D(0.0, -1.0, 0.0, 0.08));
    marks.paintShadow(QVector4D(0.0, -1.0, 0.0, 0.08));
    disk.endStencil();

    marks.beginStencil();
    arrows.paintShadow(QVector4D(0.0, -1.0, 0.0, 0.06));
    marks.endStencil();
}

void Table::paint()
{
    glEnable(GL_TEXTURE_2D);
    setupMaterial(GL_FRONT_AND_BACK, GOLD);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glPushMatrix();
    glTranslatef(0, 0, -8.85);
    RawLoader::paint();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
}

void Scene::paint()
{
    table.paint();
    clock.paint();
}

void Scene::shadows()
{
    table.shadows();
    clock.shadows();
    table.beginStencil();
    clock.paintShadow(QVector4D(0, 0, 1.0, 1.35));
    table.endStencil();
}
