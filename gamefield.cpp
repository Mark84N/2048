#include "gamefield.h"

GameField::GameField(QObject *parent, qint32 side, ITileGenerator *tileGen)
    :
    QObject(parent),
    firstRun(true),
    sideSize(side),
    lastHighScore(0),
    currentHighScore(0),
    currentLevel(static_cast<qint32>(ConstantValues::START_VALUE)),
    tileGenerator(tileGen)
{
    installNewField(side);
}

GameField::~GameField()
{
    delete tileGenerator;
}

void GameField::installNewField(qint32 side)
{
    fieldOfTiles.clear();

    sideSize = side;
    firstRun = true;
    currentHighScore = 0;
    lastHighScore = 0;

    fieldOfTiles.resize(sideSize);
    for(int x = 0; x < sideSize; x++)
    {
        fieldOfTiles[x].resize(sideSize);

        for (int y = 0; y < sideSize; y++)
        {
            fieldOfTiles[x][y].setValue(0);
        }
    }

    addNewTiles();
    copyOfField = fieldOfTiles;

    emit playerScoreChanged(currentHighScore);
}

void GameField::recalculateTilesSize(const QRect& r)
{
    int tileHeight = r.height() / sideSize;
    int tileWidth = r.width() / sideSize;

    int startHeightPoint = 0;
    int startWidthPoint = 0;

    int borderOffset = static_cast<int>(ConstantValues::BORDER_OFFSET);
    int betweenDistance = static_cast<int>(ConstantValues::BETWEEN_DISTANCE);

    for (int i = 0; i < sideSize; i++)
    {
        startHeightPoint = i*tileHeight;
        for (int j = 0; j < sideSize; j++)
        {
            startWidthPoint = j*tileWidth;
            QRect newTileRect(startWidthPoint + borderOffset, startHeightPoint + borderOffset,
                              tileWidth - betweenDistance, tileHeight - betweenDistance);
            fieldOfTiles[i][j].setBodyRect(newTileRect);
        }
    }

    for (int i = 0; i < sideSize; i++)
    {
        for (int j = 0; j < sideSize; j++)
        {
            auto copyRect = fieldOfTiles[i][j].getBodyRect();
            copyOfField[i][j].setBodyRect(copyRect);
        }
    }
}

void GameField::addNewTiles()
{
    if(firstRun)
    {
        tileGenerator->setNewTiles(2, fieldOfTiles, sideSize);
        firstRun = false;
        return;
    }

    if (checkOverflow())
        emit playerLose(currentHighScore);

    tileGenerator->setNewTiles(1, fieldOfTiles,
                               sideSize);
}

void GameField::draw(QPainter& painter)
{
    for (int i = 0; i < sideSize; i++)
    {
        for (int j = 0; j < sideSize; j++)
        {
            Tile yetAnotherTile = fieldOfTiles[i][j];
            yetAnotherTile.draw(painter);
        }
    }
}

void GameField::performMove(int keyPressed)
{
    copyOfField = fieldOfTiles;
    lastHighScore = currentHighScore;

    resetAdditionPerformedState();
    bool addOrMovePerformed = false;

    switch(keyPressed)
    {
    case Qt::Key_Up:
        addOrMovePerformed = moveUp();
        break;
    case Qt::Key_Down:
        addOrMovePerformed = moveDown();
        break;
    case Qt::Key_Left:
        addOrMovePerformed = moveLeft();
        break;
    case Qt::Key_Right:
        addOrMovePerformed = moveRight();
        break;
    default:
        break;
    }

    if (addOrMovePerformed)
    {
        addNewTiles();
        emit playerScoreChanged(currentHighScore);
    }

    if (currentLevel == static_cast<qint32>(ConstantValues::WIN_VALUE))
        emit playerWin(currentHighScore);

    if (checkNoMovesAvailable())
        emit playerLose(currentHighScore);
}

void GameField::undo()
{
    fieldOfTiles = copyOfField;
    currentHighScore = lastHighScore;


    emit playerScoreChanged(currentHighScore);
}

bool GameField::moveUp()
{
    bool anyMovePerformed = false;

    for(int widthIndex = 0; widthIndex < sideSize; widthIndex++)
    {
        for (int heightIndex = 1; heightIndex < sideSize; heightIndex++)
        {
            Tile currentTile = fieldOfTiles[heightIndex][widthIndex];
            int currentTileValue = currentTile.getValue();

            if (0 == currentTileValue
                    || currentTile.getAdditionState())
                continue;

            for (int k = heightIndex; k > 0; k--)
            {
                if (fieldOfTiles[k-1][widthIndex].getValue() == 0)
                {
                    fieldOfTiles[k-1][widthIndex].setValue(currentTileValue);
                    fieldOfTiles[k][widthIndex].setValue(0);
                    anyMovePerformed = true;
                }
                else if (fieldOfTiles[k-1][widthIndex].getValue() == currentTileValue)
                {
                    if (!fieldOfTiles[k-1][widthIndex].getAdditionState())
                    {
                        qint32 newTileValue = currentTileValue*2;

                        if (newTileValue > currentLevel)
                            currentLevel = newTileValue;

                        fieldOfTiles[k-1][widthIndex].setValue(newTileValue);
                        fieldOfTiles[k][widthIndex].setValue(0);
                        fieldOfTiles[k-1][widthIndex].setAdditionState(true);

                        currentHighScore += newTileValue;
                        anyMovePerformed = true;
                    }
                    break;
                }
                else break;
            }
        }
    }
    return anyMovePerformed;
}

bool GameField::moveDown()
{
    bool anyMovePerformed = false;

    for(int widthIndex = 0; widthIndex < sideSize; widthIndex++)
    {
        for (int heightIndex = sideSize-1; heightIndex >= 0; heightIndex--)
        {
            Tile currentTile = fieldOfTiles[heightIndex][widthIndex];
            int currentTileValue = currentTile.getValue();

            if (0 == currentTileValue
                    || currentTile.getAdditionState())
                continue;

            for (int k = heightIndex; k < sideSize-1; k++)
            {
                if (fieldOfTiles[k+1][widthIndex].getValue() == 0)
                {
                    fieldOfTiles[k+1][widthIndex].setValue(currentTileValue);
                    fieldOfTiles[k][widthIndex].setValue(0);
                    anyMovePerformed = true;
                }
                else if (fieldOfTiles[k+1][widthIndex].getValue() == currentTileValue)
                {
                    if (!fieldOfTiles[k+1][widthIndex].getAdditionState())
                    {
                        qint32 newTileValue = currentTileValue*2;

                        if (newTileValue > currentLevel)
                            currentLevel = newTileValue;

                        fieldOfTiles[k+1][widthIndex].setValue(newTileValue);
                        fieldOfTiles[k][widthIndex].setValue(0);
                        fieldOfTiles[k+1][widthIndex].setAdditionState(true);

                        currentHighScore += newTileValue;
                        anyMovePerformed = true;
                    }
                    break;
                }
                else break;
            }
        }
    }
    return anyMovePerformed;
}

bool GameField::moveLeft()
{
    bool anyMovePerformed = false;

    for(int heightIndex = 0; heightIndex < sideSize; heightIndex++)
    {
        for (int widthIndex = 1; widthIndex < sideSize; widthIndex++)
        {
            Tile currentTile = fieldOfTiles[heightIndex][widthIndex];
            int currentTileValue = currentTile.getValue();

            if (0 == currentTileValue
                    || currentTile.getAdditionState())
                continue;

            for (int k = widthIndex; k > 0; k--)
            {
                if (fieldOfTiles[heightIndex][k-1].getValue() == 0)
                {
                    fieldOfTiles[heightIndex][k-1].setValue(currentTileValue);
                    fieldOfTiles[heightIndex][k].setValue(0);
                    anyMovePerformed = true;
                }
                else if (fieldOfTiles[heightIndex][k-1].getValue() == currentTileValue)
                {
                    if (!fieldOfTiles[heightIndex][k-1].getAdditionState())
                    {
                        qint32 newTileValue = currentTileValue*2;

                        if (newTileValue > currentLevel)
                            currentLevel = newTileValue;

                        fieldOfTiles[heightIndex][k-1].setValue(newTileValue);
                        fieldOfTiles[heightIndex][k].setValue(0);
                        fieldOfTiles[heightIndex][k-1].setAdditionState(true);

                        currentHighScore += newTileValue;
                        anyMovePerformed = true;
                    }
                    break;
                }
                else break;
            }
        }
    }
    return anyMovePerformed;
}

bool GameField::moveRight()
{
    bool anyMovePerformed = false;

    for(int heightIndex = 0; heightIndex < sideSize; heightIndex++)
    {
        for (int widthIndex = sideSize - 1; widthIndex >= 0; widthIndex--)
        {
            Tile currentTile = fieldOfTiles[heightIndex][widthIndex];
            int currentTileValue = currentTile.getValue();

            if (0 == currentTileValue
                    || currentTile.getAdditionState())
                continue;

            for (int k = widthIndex; k < sideSize-1; k++)
            {
                if (fieldOfTiles[heightIndex][k+1].getValue() == 0)
                {
                    fieldOfTiles[heightIndex][k+1].setValue(currentTileValue);
                    fieldOfTiles[heightIndex][k].setValue(0);
                    anyMovePerformed = true;
                }
                else if (fieldOfTiles[heightIndex][k+1].getValue() == currentTileValue)
                {
                    if (!fieldOfTiles[heightIndex][k+1].getAdditionState())
                    {
                        qint32 newTileValue = currentTileValue*2;

                        if (newTileValue > currentLevel)
                            currentLevel = newTileValue;

                        fieldOfTiles[heightIndex][k+1].setValue(newTileValue);
                        fieldOfTiles[heightIndex][k].setValue(0);
                        fieldOfTiles[heightIndex][k+1].setAdditionState(true);

                        currentHighScore += newTileValue;
                        anyMovePerformed = true;
                    }
                    break;
                }
                else break;
            }
        }
    }
    return anyMovePerformed;
}

void GameField::resetAdditionPerformedState()
{
    for (int i = 0; i < sideSize; i++)
        for (int j = 0; j < sideSize; j++)
            fieldOfTiles[i][j].setAdditionState(false);
}

qint32 GameField::countTilesOnField()
{
    int countPresentItems = 0;

    for (int i = 0; i < sideSize ; i++)
    {
        for(int j = 0; j < sideSize; j++)
        {
            Tile tempTile = fieldOfTiles[i][j];
            int val = tempTile.getValue();

            if (val != 0)
                countPresentItems++;
        }
    }
    return countPresentItems;
}

bool GameField::checkNoMovesAvailable()
{
    bool isGameOver = checkOverflow();

    if (isGameOver)
    {
        // loop horizontally
        for (int i = 0; i < sideSize; i++)
            for (int j = 0; j < sideSize-1; j++)
                if (fieldOfTiles[i][j].getValue() == fieldOfTiles[i][j+1].getValue())
                {
                    isGameOver = false; goto FINAL;
                }
        // loop vertically
        for (int j = 0; j < sideSize; j++)
            for (int i = 0; i < sideSize-1; i++)
                if (fieldOfTiles[i][j].getValue() == fieldOfTiles[i+1][j].getValue())
                {
                    isGameOver = false; goto FINAL;
                }
    }

FINAL:
    return isGameOver;
}

bool GameField::checkOverflow()
{
    int fieldCapacity = sideSize*sideSize;
    int countTiles = countTilesOnField();

    if (countTiles >= fieldCapacity)
    {
        return true;
    }
    return false;
}
