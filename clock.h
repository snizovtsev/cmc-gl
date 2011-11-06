#ifndef CLOCK_H
#define CLOCK_H

#include "item.h"
#include "rawloader.h"

class Clock : public Item
{
public:
    Clock();
    void paint() const;
    ~Clock();

private:
    RawLoader body;
    RawLoader marks;
    RawLoader disk;
    RawLoader legs;
    RawLoader arrow;
};

#endif // CLOCK_H
