/*
    Current class is a frame on a main window. It handles keyboard events and maintains visual representation of the Tiles.
    It actually can be called an intermediary between main window with events and GameField - the class of logic. Canvas calls
    the appropriate methods of GameField to process external events (for example key pressing events, paint and resizing events).
    Signals that were transmitted by GameField are resending to main window (player wins or lose, and score changed).
*/

#ifndef Canvas_H
#define Canvas_H

#include <QFrame>
#include <QResizeEvent>

#include "gamefield.h"

namespace Ui {
class Canvas;
}

class Canvas : public QFrame
{
    Q_OBJECT

public:

    explicit Canvas(QWidget *parent = 0, qint32 side = 4);
    ~Canvas();

    virtual void paintEvent(QPaintEvent *ev)override;
    void keyPressEvent(QKeyEvent *keyEv)override;

protected:

    virtual void resizeEvent(QResizeEvent *event)override;

public slots:

    void undo();
    void reset();
    void setAnotherField(qint32 size);

signals:

    void win(qint32 score);
    void lose(qint32 score);
    void scoreChanged(qint32 score);

private:

    GameField* gameField;
    qint32 sideSize;
};

#endif // Canvas_H
