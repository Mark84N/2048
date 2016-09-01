/*
    Current class is used by 'GameField' class for creation of the new Tiles. The cell position is chosen arbitrarily
    using std::random. The key method, setNewTiles, receives 3 arguments:
        - qint32 quantity - how many should be created
        - QVector<QVector<Tile> > &fieldOfTiles - where to create
        - qint32 sideSize - width/height of the set of Tiles in fieldOfTiles

    Firstly 'setNewTiles' was made as a static because there's no need to create an instance for this kind of generator.
    But then i thought "Whoa, shouldn't it implement some interface for customization of the creation process in the future?"
    So, now ClassicTileGenerator implements ITileGenerator interface, and 'GameField' has a pointer to ITileGenerator subclass instance.

*/

#ifndef TILEGENERATOR_H
#define TILEGENERATOR_H

#include <QVector>
#include <QTime>
#include <random>

#include "tile.h"
#include "interfaces\itilegenerator.h"


class ClassicTileGenerator: public ITileGenerator
{
public:

    ClassicTileGenerator();
    ~ClassicTileGenerator();

    virtual void setNewTiles(qint32 quantity, QVector<QVector<Tile> > &fieldOfTiles,
                            qint32 sideSize)override;

};

#endif // TILEGENERATOR_H
