QT       += core gui opengl

TARGET = cmc-gl
TEMPLATE = app
LIBS = -lglut

SOURCES += main.cpp \
    glwindow.cpp \
    rawloader.cpp \
    clock.cpp \
    materials.cpp

HEADERS  += \
    glwindow.h \
    item.h \
    clock.h \
    rawloader.h \
    materials.h
