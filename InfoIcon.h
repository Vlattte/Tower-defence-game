#ifndef INFOICON_H
#define INFOICON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class InfoIcon: public QGraphicsPixmapItem
{
public:
    InfoIcon(QGraphicsItem* parent = 0);

    void mousePressEvent (QGraphicsSceneMouseEvent * event);

};

#endif // INFOICON_H
