#include "clock.h"
#include "materials.h"
#include <QTime>

Clock::Clock()
    : body("models/body.ply"),
      marks("models/marks.ply"),
      disk("models/disk.ply"),
      legs("models/legs.ply"),
      arrow("models/arrow.ply")
{
}

Clock::~Clock()
{

}

void Clock::paint() const
{
    setupMaterial(GL_FRONT_AND_BACK, GREEN_PLASTIC);
    glPushMatrix();
        glScalef(0.10, 0.10, 0.10);
        body.paint();
    glPopMatrix();

    setupMaterial(GL_FRONT_AND_BACK, TURQUOISE);
    glPushMatrix();
        glScalef(0.10, 0.10, 0.10);
        disk.paint();
    glPopMatrix();

    setupMaterial(GL_FRONT_AND_BACK, SILVER);
    glPushMatrix();
        glTranslatef(-0.767, 0.5, 1.276);
        glScalef(0.10, 0.10, 0.10);
        legs.paint();
    glPopMatrix();

    setupMaterial(GL_FRONT, COPPER);
    setupMaterial(GL_BACK, BRONZE);
    glPushMatrix();
        glTranslatef(0.0f, 0.07f, 0.0f);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        marks.paint();
    glPopMatrix();

    setupMaterial(GL_FRONT_AND_BACK, BLACK_PLASTIC);
    QTime time = QTime::currentTime();
    glPushMatrix();
        glRotatef(90.0, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, -0.04);
        glPushMatrix();
            glRotatef(360.0 / 60.0 * time.minute(), 0, 0, -1.0);
            arrow.paint();
        glPopMatrix();
        glPushMatrix();
            glRotatef(360.0 / 12.0 * (time.hour() % 12 + time.minute() / 60.0), 0, 0, -1.0);
            glScalef(1.0, 0.681, 1.0);
            glTranslatef(0.0, 0.0, -0.02);
            arrow.paint();
        glPopMatrix();
        glPushMatrix();
            glRotatef(360.0 / 60.0 * QTime::currentTime().second(), 0, 0, -1.0);
            glScalef(0.2, 1.0, 1.0);
            glTranslatef(0.0, 0.0, 0.02);
            arrow.paint();
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

