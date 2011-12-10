#ifndef RAWLOADER_H
#define RAWLOADER_H

#include "plugin.h"

struct Geometry;

class GeometryItem: public Item
{
    Geometry* geom;
public:
    explicit GeometryItem(Geometry* _geom): geom(_geom) { }
    ~GeometryItem();

    void paint();
    void shadows() { }
    const char* id() const { return "<geometryItem>"; }
};

class RawLoader: public Loader
{
public:
    GeometryItem* load(const char *fileName);

    const char* accept() const
    {
        return "raw";
    }
};

class RawLoaderFactory: public Factory<Loader> {
public:
    Loader* create() const { return new RawLoader(); }
};

#endif // RAWLOADER_H
