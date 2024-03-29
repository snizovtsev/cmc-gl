#include "materials.h"
#include "pluginimpl.h"

const GLfloat material_table[24][11] = {
    {0.0215,    0.1745,    0.0215,    .1,  0.07568,   0.61424,     0.07568,     0.633,       0.727811,    0.633,       0.6},
    {0.135,     0.2225,    0.1575,    .1,  0.54,      0.89,        0.63,        0.316228,    0.316228,    0.316228,    0.1},
    {0.05375,   0.05,      0.06625,   .1,  0.18275,   0.17,        0.22525,     0.332741,    0.328634,    0.346435,    0.3},
    {0.25,      0.20725,   0.20725,   .1,  1,         0.829,       0.829,       0.296648,    0.296648,    0.296648,    0.088},
    {0.1745,    0.01175,   0.01175,   .1,  0.61424,   0.04136,     0.04136,     0.727811,    0.626959,    0.626959,    0.6},
    {0.1,       0.18725,   0.1745,    .1,  0.396,     0.74151,     0.69102,     0.297254,    0.30829,     0.306678,    0.1},
    {0.329412,  0.223529,  0.027451,  .1,  0.780392,  0.568627,    0.113725,    0.992157,    0.941176,    0.807843,    0.21794872},
    {0.2125,    0.1275,    0.054,     .1,  0.714,     0.4284,      0.18144,     0.393548,    0.271906,    0.166721,    0.2},
    {0.25,      0.25,      0.25,      .1,  0.4,       0.4,         0.4,         0.774597,    0.774597,    0.774597,    0.6},
    {0.19125,   0.0735,    0.0225,    .1,  0.7038,    0.27048,     0.0828,      0.256777,    0.137622,    0.086014,    0.1},
    {0.24725,   0.1995,    0.0745,    .1,  0.75164,   0.60648,     0.22648,     0.628281,    0.555802,    0.366065,    0.4},
    {0.19225,   0.19225,   0.19225,   .1,  0.50754,   0.50754,     0.50754,     0.508273,    0.508273,    0.508273,    0.4},
    {0.0,       0.0,       0.0,       .1,  0.01,      0.01,        0.01,        0.50,        0.50,        0.50,        .25},
    {0.0,       0.1,       0.06,      .1,  0.0,       0.50980392,  0.50980392,  0.50196078,  0.50196078,  0.50196078,  .25},
    {0.0,       0.0,       0.0,       .1,  0.1,       0.35,        0.1,         0.45,        0.55,        0.45,        .25},
    {0.0,       0.0,       0.0,       .1,  0.5,       0.0,         0.0,         0.7,         0.6,         0.6,         .25},
    {0.0,       0.0,       0.0,       .1,  0.55,      0.55,        0.55,        0.70,        0.70,        0.70,        .25},
    {0.0,       0.0,       0.0,       .1,  0.5,       0.5,         0.0,         0.60,        0.60,        0.50,        .25},
    {0.02,      0.02,      0.02,      .1,  0.01,      0.01,        0.01,        0.4,         0.4,         0.4,         .078125},
    {0.0,       0.05,      0.05,      .1,  0.4,       0.5,         0.5,         0.04,        0.7,         0.7,         .078125},
    {0.0,       0.05,      0.0,       .1,  0.4,       0.5,         0.4,         0.04,        0.7,         0.04,        .078125},
    {0.05,      0.0,       0.0,       .1,  0.5,       0.4,         0.4,         0.7,         0.04,        0.04,        .078125},
    {0.05,      0.05,      0.05,      .1,  0.5,       0.5,         0.5,         0.7,         0.7,         0.7,         .078125},
    {0.05,      0.05,      0.0,       .1,  0.5,       0.5,         0.4,         0.7,         0.7,         0.04,        .078125}
};

void PluginImpl::setupMaterial(GLenum face, enum Material material) const
{
    const GLfloat* entry = material_table[material];
    glMaterialfv(face, GL_AMBIENT, entry);
    glMaterialfv(face, GL_DIFFUSE, entry + 4);
    glMaterialfv(face, GL_SPECULAR, entry + 4 + 3);
    glMaterialf(face, GL_SHININESS,  entry[10] * 128.0);
}
