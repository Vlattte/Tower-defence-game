#include "InfoIcon.h"
#include "Info.h"
#include "game.h"

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
        game->pause = -1;

        //change position of the window
        QPointF point = mapToScene(event->pos());
        int windowX = point.x() + 190;
        int windowY = point.y() + 90;

        //set the window
        Info window;
        window.setWindowTitle("Information");
        window.move(windowX, windowY);
        window.setModal(true);
        window.exec();
    }
}
