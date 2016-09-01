#include "canvas.h"

#include <qdebug.h>

Canvas::Canvas(QWidget *parent, qint32 side)
    : QFrame(parent),
      sideSize(side)
{
    gameField = new GameField(this, side, new ClassicTileGenerator());

    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setFocusPolicy(Qt::StrongFocus);

    QPalette pal;
    pal.setColor(QPalette::Window, QColor::fromRgb(187,173,160));

    this->setPalette(pal);
    this->setAutoFillBackground(true);

    connect(gameField, SIGNAL(playerLose(qint32)), SIGNAL(lose(qint32)));
    connect(gameField, SIGNAL(playerWin(qint32)), SIGNAL(win(qint32)));
    connect(gameField, SIGNAL(playerScoreChanged(qint32)), SIGNAL(scoreChanged(qint32)));
}

Canvas::~Canvas()
{
    delete gameField;
}

void Canvas::paintEvent(QPaintEvent *ev)
{
    QFrame::paintEvent(ev);

    QPainter painter(this);
    painter.drawRect(this->rect());

    gameField->draw(painter);
}

void Canvas::reset()
{
    gameField->installNewField(sideSize);
    gameField->recalculateTilesSize(rect());
    update();
}

void Canvas::setAnotherField(qint32 size)
{
    sideSize = size;
    gameField->installNewField(sideSize);
    gameField->recalculateTilesSize(rect());
    update();
}

void Canvas::keyPressEvent(QKeyEvent *keyEv)
{
    if ((keyEv->key() == Qt::Key_Z))
    {
        update();

        gameField->undo();
        qDebug() << "z";

    }
    if ((keyEv->modifiers() & Qt::ControlModifier) )
    {

        qDebug() << "ctrl";

        if ((keyEv->key() == Qt::Key_Z))
        {
            update();

            gameField->undo();
            qDebug() << "z";

        }
    }
    else
    {
        gameField->performMove(keyEv->key());
    }

    update();
}

void Canvas::resizeEvent(QResizeEvent *event)
{
    gameField->recalculateTilesSize(rect());
}

void Canvas::undo()
{
    gameField->undo();
    update();
}
