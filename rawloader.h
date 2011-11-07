#ifndef RAWLOADER_H
#define RAWLOADER_H

#include "item.h"

struct Geometry;

class RawLoader : public Item
{
public:
    explicit RawLoader(const char* fileName);
    void paint();

    ~RawLoader();
private:
    Geometry* geom;
};

#endif // RAWLOADER_H
