#ifndef ITEM_H
#define ITEM_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include <QVector4D>

class Item {
public:
    virtual void paint() = 0;
    void paintShadow(const QVector4D& plane);
    virtual ~Item() { }
};

#endif // ITEM_H
