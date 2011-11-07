#include "item.h"

#include <QMatrix4x4>

QVector4D getLight(GLenum lightNo)
{
    QMatrix4x4 modelView;
    GLfloat lightPos[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelView.data());
    glGetLightfv(lightNo, GL_POSITION, lightPos);

    return modelView.inverted() * QVector4D(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
}

void Item::paintShadow(const QVector4D& plane)
{
    QVector4D light = getLight(GL_LIGHT0);
    qreal dot = QVector4D::dotProduct(light, plane);

    GLdouble matrix[4][4];
    matrix[0][0] = dot  - light.x() * plane.x();
    matrix[1][0] = 0.0f - light.x() * plane.y();
    matrix[2][0] = 0.0f - light.x() * plane.z();
    matrix[3][0] = 0.0f - light.x() * plane.w();

    matrix[0][1] = 0.0f - light.y() * plane.x();
    matrix[1][1] = dot  - light.y() * plane.y();
    matrix[2][1] = 0.0f - light.y() * plane.z();
    matrix[3][1] = 0.0f - light.y() * plane.w();

    matrix[0][2] = 0.0f - light.z() * plane.x();
    matrix[1][2] = 0.0f - light.z() * plane.y();
    matrix[2][2] = dot  - light.z() * plane.z();
    matrix[3][2] = 0.0f - light.z() * plane.w();

    matrix[0][3] = 0.0f - light.w() * plane.x();
    matrix[1][3] = 0.0f - light.w() * plane.y();
    matrix[2][3] = 0.0f - light.w() * plane.z();
    matrix[3][3] = dot  - light.w() * plane.w();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHTING);

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);

    glPushMatrix();
    glMultMatrixd(&matrix[0][0]);
    paint();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    glDisable(GL_BLEND);
}
