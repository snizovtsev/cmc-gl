QT += core gui opengl

TARGET = cmc-gl
TEMPLATE = app

SOURCES += main.cpp \
    glwindow.cpp \
    materials.cpp \
    item.cpp \
    pluginimpl.cpp

HEADERS  += \
    glwindow.h \
    materials.h \
    plugin.h \
    pluginimpl.h
