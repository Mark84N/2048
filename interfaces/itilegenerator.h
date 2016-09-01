#ifndef ITILEGENERATOR_H
#define ITILEGENERATOR_H

#include <QVector>
#include <tile.h>

class ITileGenerator
{
public:

    ITileGenerator() {}
    ~ITileGenerator() {}

    virtual void setNewTiles(qint32 quantity, QVector<QVector<Tile> > &fieldOfTiles,
                            qint32 sideSize)=0;

};

#endif // ITILEGENERATOR_H
