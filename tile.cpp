#include "tile.h"

Tile::Tile(const QRect &sourceBody, qint32 val)
    :additionIndicator(false),
      value(val),
      body(sourceBody)

{
}

Tile::Tile()
    :additionIndicator(false),
      value(0),
      body()

{
}

QRect Tile::getBodyRect()const
{
    return body;
}

void Tile::setBodyRect(const QRect &sourceBody)
{
    body = sourceBody;
}

qint32 Tile::getValue() const
{
    return value;
}

void Tile::setValue(qint32 val)
{
    value = val;
}

void Tile::setAdditionState(bool wasAdditionPerformed)
{
    additionIndicator = wasAdditionPerformed;
}

bool Tile::getAdditionState()
{
    return additionIndicator;
}

void Tile::draw(QPainter &painter)
{
    QColor customColor = getTileColor(value);

    QBrush customBrush(customColor);
    painter.setBrush(customBrush);

    QColor penColor = customColor;
    painter.setPen(penColor);

    QFont font = painter.font();
    font.setPixelSize(25);
    font.setBold(true);
    font.setStyleHint(QFont::SansSerif);

    painter.setFont(font);

    painter.setRenderHint(QPainter::Antialiasing);
    //painter.fillRect(body, customBrush);
    painter.drawRoundRect(body, 20,20);

    penColor = getPenColor(value);
    painter.setPen(penColor);

    if (value != 0)
        painter.drawText(body, Qt::AlignCenter, QString::number(value));
}

QColor Tile::getTileColor(qint32 value)
{
    QColor color;

    switch(value)
    {
    case 0:
        color = QColor::fromRgb(204,192,179);
        break;
    case 2:
        color = QColor::fromRgb(238, 228, 218);
        break;
    case 4:
        color = QColor::fromRgb(237, 224, 200);
        break;
    case 8:
        color = QColor::fromRgb(242,177,121);
        break;
    case 16:
        color = QColor::fromRgb(245,149,99);
        break;
    case 32:
        color = QColor::fromRgb(246,124,95);
        break;
    case 64:
        color = QColor::fromRgb(233, 88, 57);
        break;
    case 128:
        color = QColor::fromRgb(244,216,109);
        break;
    case 256:
        color = QColor::fromRgb(241,208,75);
        break;
    case 512:
        color = QColor::fromRgb(229,192,43);
        break;
    case 1024:
        color = QColor::fromRgb(236,196,0);
        break;
    case 2048:
        color = QColor::fromRgb(236,196,0);
        break;
    }
    return color;
}

QColor Tile::getPenColor(qint32 value)
{
    QColor color;

    switch(value)
    {
    case 0:case 2:case 4:
        color = QColor::fromRgb(119,110,101);
        break;
    default:
        color = Qt::white;
        break;
    }
    return color;
}
