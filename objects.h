#ifndef CLOCK_H
#define CLOCK_H

#include "item.h"
#include "rawloader.h"

class Arrows: public RawLoader
{
public:
    Arrows(): RawLoader("models/arrow.ply") { }
    ~Arrows() { }
    void paint();
};

class Body: public RawLoader
{
public:
    Body(): RawLoader("models/body.ply") { }
    ~Body() { }
    void paint();
};

class Marks: public RawLoader
{
public:
    Marks(): RawLoader("models/marks.ply") { }
    ~Marks() { }
    void paint();
};

class Legs: public RawLoader
{
public:
    Legs(): RawLoader("models/legs.ply") { }
    ~Legs() { }
    void paint();
};

class Disk: public RawLoader
{
public:
    Disk(): RawLoader("models/disk.ply") { }
    ~Disk() { }
    void paint();
};

class Clock : public Item
{
public:
    Clock() { }
    ~Clock() { }

    void paint();
    void shadows();

private:
    Body body;
    Marks marks;
    Legs legs;
    Arrows arrows;
    Disk disk;
};

class Table: public RawLoader
{
public:
    Table(): RawLoader("models/table.ply") { }
    ~Table() { }
    void paint();
};

class Scene: Item
{
public:
    Scene() { }
    ~Scene() { }

    void paint();
    void shadows();

private:
    Clock clock;
    Table table;
};

#endif // CLOCK_H
