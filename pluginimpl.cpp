#include "pluginimpl.h"

PluginImpl::PluginImpl()
{
}

PluginImpl::~PluginImpl()
{
}

void PluginImpl::registerItem(const Factory<Item> &item)
{
    Item* instance = item.create();
    if (items.contains(instance->id())) {
        qDebug() << instance->id() << "is already registered, ignoring...";
        return;
    }

    items[instance->id()] = instance;
}

void PluginImpl::registerLoader(const Factory<Loader> &loader)
{
    Loader* instance = loader.create();
    if (loaders.contains(instance->accept()) || strcmp(instance->accept(), "item") == 0) {
        qDebug() << instance->accept() << "is already supported, ignoring...";
        return;
    }

    loaders[instance->accept()] = instance;
}

Item* PluginImpl::getItem(const char *id)
{
    if (items.contains(id))
        return items[id];

    QStringList path = QString(id).split(":");
    if (path.count() != 2) {
        qDebug() << "paintItem: wrong path";
        return 0;
    }

    if (path[0] == "item") {
        if (!items.contains(path[1])) {
            qDebug() << "paintItem: No such item:" << path[1];
            return 0;
        }

        return items[path[1]];
    }

    if (!loaders.contains(path[0])) {
        qDebug() << path[0] << "is not supported";
        return 0;
    }

    Item* item = loaders[path[0]]->load(qPrintable(path[1]));
    if (item == 0) {
        qDebug() << "Can't load" << path[1];
        return item;
    }

    return items[id] = item;
}
