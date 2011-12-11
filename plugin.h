#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtCore>
#include "materials.h"

class Interface {
public:
    virtual Q_DECL_EXPORT ~Interface() { }
};

template<class InterfaceType>
class Factory {
public:
    virtual Q_DECL_EXPORT InterfaceType* create() const = 0;
};

class Item: public Interface {
public:
    virtual Q_DECL_EXPORT void paint() = 0;
    virtual Q_DECL_EXPORT void shadows() = 0;
    virtual Q_DECL_EXPORT const char* id() const = 0;
};

class Loader: public Interface {
public:
    virtual Q_DECL_EXPORT Item* load(const char* fileName) = 0;
    virtual Q_DECL_EXPORT const char* accept() const = 0;
};

class Plugin: public Interface {
public:
    virtual Q_DECL_IMPORT void  registerLoader(const Factory<Loader> &loaderFactory) = 0;
    virtual Q_DECL_IMPORT void  registerItem(const Factory<Item> &itemFactory) = 0;
    virtual Q_DECL_IMPORT Item* getItem(const char* id)  = 0;

    virtual Q_DECL_IMPORT void  paintShadow(Item* item, const QVector4D& plane) const = 0;
    virtual Q_DECL_IMPORT void  paintShadow(const char* itemID, const QVector4D& plane) = 0;

    virtual Q_DECL_IMPORT void  beginStencil(Item* item) const = 0;
    virtual Q_DECL_IMPORT void  beginStencil(const char* itemID) = 0;
    virtual Q_DECL_IMPORT void  endStencil() const = 0;

    virtual Q_DECL_IMPORT void  setupMaterial(GLenum face, enum Material material) const = 0;
};

extern "C" typedef void (*EntryPointProto)(Plugin* _plugin);

#endif // PLUGIN_H
