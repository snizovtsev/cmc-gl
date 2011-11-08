#ifndef ITEM_H
#define ITEM_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>
#include <QVector4D>

class Item {
public:
    Item() { }
    virtual ~Item() { }

    virtual void paint() = 0;
    virtual void shadows() { }

    void paintShadow(const QVector4D& plane);
    void beginStencil();
    void endStencil();

protected:
    bool with_shadows;
};

#endif // ITEM_H
