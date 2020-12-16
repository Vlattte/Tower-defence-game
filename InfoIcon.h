#ifndef INFOICON_H
#define INFOICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>

class Info;

class InfoIcon: public QGraphicsPixmapItem
{
public:
    InfoIcon(QGraphicsItem* parent = 0);

    void mousePressEvent (QGraphicsSceneMouseEvent * event);

    Info *window;
};

#endif // INFOICON_H
