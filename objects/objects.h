#ifndef OBJECTS_H
#define OBJECTS_H

#include <GL/glu.h>

#include "plugin.h"

class ModelItem: public Item
{
protected:
    const char* const modelFile;
    explicit ModelItem(const char* const file): modelFile(file) { }
};

class Arrows: public ModelItem
{
    GLUquadric* stick;
public:
    Arrows();
    ~Arrows();
    void paint();
    void shadows() { }
    const char* id() const { return "arrows"; }
};
FACTORY(Arrows);

class Body: public ModelItem
{
public:
    Body(): ModelItem("raw:models/body.ply") { }
    ~Body() { }
    void paint();
    void shadows() { }
    const char* id() const { return "body"; }
};
FACTORY(Body);

class Marks: public ModelItem
{
public:
    Marks(): ModelItem("raw:models/marks.ply") { }
    ~Marks() { }
    void paint();
    void shadows() { }
    const char* id() const { return "marks"; }
};
FACTORY(Marks);

class Legs: public ModelItem
{
public:
    Legs(): ModelItem("raw:models/legs.ply") { }
    ~Legs() { }
    void paint();
    void shadows() { }
    const char* id() const { return "legs"; }
};
FACTORY(Legs);

class Disk: public ModelItem
{
public:
    Disk(): ModelItem("raw:models/disk.ply") { }
    ~Disk() { }
    void paint();
    void shadows() { }
    const char* id() const { return "disk"; }
};
FACTORY(Disk);

class Clock : public Item
{
public:
    Clock() { }
    ~Clock() { }

    void paint();
    void shadows();
    const char* id() const { return "clock"; }
};
FACTORY(Clock);

class Table: public ModelItem
{
public:
    Table(): ModelItem("raw:models/table.ply") { }
    ~Table() { }

    void paint();
    void shadows() { }
    const char* id() const { return "table"; }
};
FACTORY(Table);

class Scene: public Item
{
public:
    Scene() { }
    ~Scene() { }

    void paint();
    void shadows();
    const char* id() const { return "scene"; }
};
FACTORY(Scene);

#endif // OBJECTS_H
