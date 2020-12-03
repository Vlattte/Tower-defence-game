#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class PauseButton: public QGraphicsPixmapItem
{
public:
    PauseButton(QGraphicsItem * parent = 0);

    void mousePressEvent (QGraphicsSceneMouseEvent * event);
};

#endif // PAUSEBUTTON_H
