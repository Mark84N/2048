#include "classictilegenerator.h"

ClassicTileGenerator::ClassicTileGenerator(){}

ClassicTileGenerator::~ClassicTileGenerator(){}

void ClassicTileGenerator::setNewTiles(qint32 quantity, QVector<QVector<Tile>>& fieldOfTiles,
                                qint32 sideSize)
{
    int xIndex;
    int yIndex;
    int probabilityValue;
    int generatedValue;

    QTime midnight(0,0,0);

    std::mt19937 generator;
    generator.seed(QTime::currentTime().msecsTo(midnight));

    std::uniform_int_distribution<int> generatorDistribution(0, sideSize-1);

    for (int i = 0; i < quantity; i++)
    {
        do
        {
            xIndex = generatorDistribution(generator);
            yIndex = generatorDistribution(generator);
        }
        while(fieldOfTiles[xIndex][yIndex].getValue() != 0);

        probabilityValue = generatorDistribution(generator); // probability of tile.value==4 is 1/4, i.e. 25%
        generatedValue = (probabilityValue == 0? 4 : 2);     // tile with value 2 or 4

        fieldOfTiles[xIndex][yIndex].setValue(generatedValue);
    }
}


