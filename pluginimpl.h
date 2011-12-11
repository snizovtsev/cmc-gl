#ifndef PLUGINIMPL_H
#define PLUGINIMPL_H

#include <QtCore>
#include "plugin.h"

class PluginImpl : public Plugin
{
    QMap <QString, Loader*> loaders;
    QMap <QString, Item*>   items;
public:
    PluginImpl();

    void registerLoader(const Factory<Loader> &loaderFactory);
    void registerItem(const Factory<Item> &itemFactory);
    Item* getItem(const char *id);

    void paintShadow(Item* item, const QVector4D& plane) const;
    void paintShadow(const char* itemID, const QVector4D& plane);

    void beginStencil(Item* item) const;
    void beginStencil(const char* itemID);
    void endStencil() const;

    void setupMaterial(GLenum face, Material material) const;

    ~PluginImpl();
};

#endif // PLUGINIMPL_H
