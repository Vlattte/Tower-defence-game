#include "Pausebutton.h"
#include "game.h"

extern Game * game;

PauseButton::PauseButton(QGraphicsItem * parent)
{
    setPixmap(QPixmap(":/images/images/pause.png"));
}

void PauseButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //turn on and off the pause
    if (event->button() == Qt::RightButton ||
        event->button() == Qt::LeftButton)
    {
        game->pause *= -1;
    }
}
