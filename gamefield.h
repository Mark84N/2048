/*
    GameField is a class of main game logic, where all depends on the interaction between tiles.

    About field:

    1. field is a 2-dimensional vector of tiles, which are the cells on the screen
    2. new custom-sized fields (e.g. 4x4, 5x5...) can be installed using 'installNewField(const QRect &rect, qint32 size)',
        where:
        - rect is the rectangle that represents the entire area of the parent widget (parent widget here is Canvas);
        - size means side of the square (i.e. how many Tiles are in rows/columns (rows == columns!))
    3. 'fieldOfTiles' is represented on Canvas as a set of small equal rectangles.

    About Tiles:

    1. each tile at the start of a new game has value == 0 and it value is not displayed (see Tile::draw(QPainter&));
    2. custom Tile values (e.g. 2,4,8,16...) are set in 'addNewTiles()', in its turn it is using ClassicTileGenerator;
    3. every Tile has QRect as the member variable - it is responsible for correct placement on Canvas widget;
        Method 'recalculateTilesSize(const QRect& r)' take the rectangle of Canvas (coordinates of it's entire body)
        and divides it into smaller equal rectangles depeding on the size of 'fieldOfTiles' (4x4 means 16 tiles on Canvas, etc.)
    4. every time main window is resized, or 'installNewField(...)' is called - p.3 is executed;

    Moving and other events:

    1. key press events are received in parent widget (Canvas), parent calls 'performMove()' of GameField and it is used to check the
    direction and call an appropriate method among:  moveUp();  moveDown();  moveLeft();  moveRight();
    2. class GameField traces current game state (won/lose/score changed) and emits signals for listeners;

*/

#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QObject>
#include <QKeyEvent>

#include "classictilegenerator.h"
#include "tile.h"

enum class ConstantValues{ START_VALUE = 2, WIN_VALUE = 2048, BORDER_OFFSET = 4, BETWEEN_DISTANCE = 8 };

class GameField: public QObject
{
    Q_OBJECT

public:

    GameField(QObject *parent, const QRect &rect, qint32 side,
              ITileGenerator* tileGen = new ClassicTileGenerator());
    ~GameField();

    void installNewField(const QRect &rect, qint32 size);
    void recalculateTilesSize(const QRect& r);
    void addNewTiles();
    void draw(QPainter &painter);

    void performMove(int keyPressed);
    void undo();

signals:

    void playerWin(qint32 score);
    void playerLose(qint32 score);
    void playerScoreChanged(qint32 score);

private:

    bool firstRun;
    qint32 sideSize;
    qint32 lastHighScore;
    qint32 currentHighScore;
    qint32 currentLevel;
    ITileGenerator *tileGenerator;

    QVector<QVector<Tile>>fieldOfTiles;
    QVector<QVector<Tile>>copyOfField;  // copy of tiles for undo feature

    // moving logic
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    // utility
    void resetAdditionPerformedState(); // see in tile.h 'additionPerformed' explanation
    qint32 countTilesOnField();         // counts tiles only with non-0 values
    bool checkNoMovesAvailable();
    bool checkOverflow();               // true if all cells are full
};

#endif // GAMEFIELD_H
