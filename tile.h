/*
    Current class represents a single Tile on the game canvas, which is actually a rectangle.
    So class Tile encapsulates its body rectangle (coordinates relative to game's canvas), and integer value (2,4,8 etc.).
    Each tile draws itself using QPainter of game canvas. Color depends on the tile value, so it's chosen in runtime using
    static method 'getTileColor(qint32 value)'.

    One significant moment: boolean value additionIndicator serves to check whether current Tile has been already summed with
    another one, or not. During one game step (one button press), one Tile can only be summed with strictly one another Tile.
    For example: if user pressed Right Arrow (right move), and Tiles 4,2,2 placed horizontally in the canvas:
    Once 2 and 2 is summed, canvas looks like as 4,4. They will not be added on current iteration, because one of 4 was in action
    a moment before.

*/

#ifndef TILE_H
#define TILE_H

#include <QRect>
#include <QPainter>
#include <QBrush>
#include <QColor>

class Tile
{
public:

    Tile(const QRect &sourceBody, qint32 val);
    Tile();

    QRect getBodyRect()const;
    void setBodyRect(const QRect &sourceBody);

    qint32 getValue()const;
    void setValue(qint32 val);

    void setAdditionState(bool wasAdditionPerformed);
    bool getAdditionState();

    void draw(QPainter& painter);

private:

    bool additionIndicator;
    qint32 value;
    QRect body;

    static QColor getTileColor(qint32 value);
    static QColor getPenColor(qint32 value);
};

#endif // TILE_H
