#include <QMatrix4x4>

#include "pluginimpl.h"

QVector4D getLight(GLenum lightNo)
{
    QMatrix4x4 modelView;
    GLfloat lightPos[4];

    glGetDoublev(GL_MODELVIEW_MATRIX, modelView.data());
    glGetLightfv(lightNo, GL_POSITION, lightPos);

    return modelView.inverted() * QVector4D(lightPos[0], lightPos[1], lightPos[2], lightPos[3]);
}

void PluginImpl::paintShadow(Item* item, const QVector4D &plane) const
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
    //glEnable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_LIGHTING);

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);

    glPushMatrix();
    glMultMatrixd(&matrix[0][0]);
    item->paint();
    glPopMatrix();

    glEnable(GL_LIGHTING);
    //glDisable(GL_POLYGON_OFFSET_FILL);
    glDisable(GL_BLEND);
}

void PluginImpl::paintShadow(const char *itemID, const QVector4D &plane)
{
    paintShadow(getItem(itemID), plane);
}

void PluginImpl::beginStencil(Item *item) const
{
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glClearStencil(0);

    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xffffffff);

    glDisable(GL_LIGHTING);
    item->paint();
    glEnable(GL_LIGHTING);

    glStencilFunc(GL_EQUAL, 1, 0xffffffff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);
}

void PluginImpl::beginStencil(const char *itemID)
{
    beginStencil(getItem(itemID));
}

void PluginImpl::endStencil() const
{
    glDisable(GL_STENCIL_TEST);
}
