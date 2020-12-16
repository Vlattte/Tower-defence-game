#include "InfoIcon.h"
#include "Info.h"
#include "game.h"
#include <QDebug>

extern Game * game;

InfoIcon::InfoIcon(QGraphicsItem * parent)
{
    //set pixmap
    setPixmap(QPixmap(":/images/images/info.png"));


}

void InfoIcon::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //if clicked on info
    if (event->button() == Qt::LeftButton
     || event->button() == Qt::RightButton)
    {
        QPointF point = event->scenePos();
        if(!this->sceneBoundingRect().intersects(QRectF(point.x(), point.y(), 1, 1))){
            event->ignore();
            return;
        }

        game->pause = -1;


        window = new Info;
        window->setWindowTitle("Information");
        window->setModal(true);
        window->exec();
        window->close();

        game->pause = 1;
    }
}
