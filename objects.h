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

class Clock : public Item
{
public:
    Clock();
    void paint();
    ~Clock();

private:
    RawLoader body;
    RawLoader marks;
    RawLoader disk;
    RawLoader legs;
    Arrows arrows;
};

#endif // CLOCK_H
