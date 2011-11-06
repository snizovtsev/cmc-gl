#ifndef ITEM_H
#define ITEM_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>

class Item {
public:
    virtual void paint() const = 0;
    virtual ~Item() { }
};

#endif // ITEM_H
