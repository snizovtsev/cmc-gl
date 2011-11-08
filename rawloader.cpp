#include "rawloader.h"

#include <QtCore>
#include <QVector2D>
#include <QVector3D>

struct Geometry {
    QVector<GLushort> faces;
    QVector<QVector3D> vertices;
    QVector<QVector3D> normals;
    QVector<QVector2D> texCoords;
    GLenum faceMode;

    void loadArrays() const;
};

void Geometry::loadArrays() const
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glNormalPointer(GL_FLOAT, 0, normals.constData());
    if (!texCoords.empty())
        glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
}

RawLoader::RawLoader(const char* fileName)
{
    geom = new Geometry();

    QFile data(fileName);
    if (!data.open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can't open " << fileName;
    QTextStream stream(&data);

    int nvert, nface;
    stream >> nvert >> nface;

    geom->vertices.reserve(nvert);
    geom->normals.reserve(nvert);
    geom->faces.reserve(nface);

    for (int i = 0; i < nvert; ++i) {
        float x, y, z;

        stream >> x >> y >> z;
        geom->vertices.append(QVector3D(x, y, z));
        stream >> x >> y >> z;
        geom->normals.append(QVector3D(x, y, z));

        QTextStream tail(stream.readLine().toAscii());
        tail.skipWhiteSpace();
        if (!tail.atEnd()) {
            tail >> x >> y;
            geom->texCoords.append(QVector2D(x, y));
        }
    }

    geom->faceMode = 0;
    for (int i = 0; i < nface; ++i) {
        int n; stream >> n;
        if (geom->faceMode == 0)
            geom->faceMode = (n == 3) ? GL_TRIANGLES : GL_QUADS;
        Q_ASSERT((n == 4 && geom->faceMode == GL_QUADS) ||
                 (n == 3 && geom->faceMode == GL_TRIANGLES));

        for (int j = 0; j < n; ++j) {
            GLushort index;
            stream >> index;
            geom->faces.append(index);
        }
    }
}

RawLoader::~RawLoader()
{
    delete geom;
}

void RawLoader::paint()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    if (!geom->texCoords.empty())
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    geom->loadArrays();
    glDrawElements(geom->faceMode, geom->faces.count(),
                   GL_UNSIGNED_SHORT,geom->faces.constData());

    if (!geom->texCoords.empty())
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
