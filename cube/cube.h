#ifndef CUBE_H
#define CUBE_H

#include "GL/glu.h"

#include "plugin.h"

namespace {
class Cube: public Item
{
    GLUquadric* sphere;
public:
    Cube();
    ~Cube();
    void paint();
    void shadows() { }
    const char* id() const { return "cube"; }
};
FACTORY(Cube);

class CubeScene: public Item
{
public:
    CubeScene() { }
    ~CubeScene() { }
    void paint();
    void shadows();
    const char* id() const { return "cubeScene"; }
};
FACTORY(CubeScene);
}

#endif // CUBE_H
