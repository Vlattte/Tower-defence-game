#include "Bone.h"
#include "game.h"
#include "Base.h"

#include <QTimer>
#include <qmath.h>
#include <QList>
#include <QMessageBox>

extern Game * game;

Bone::Bone(QGraphicsItem * parent)
{
    //set pixmap
    setPixmap(QPixmap(":/images/images/bone.png"));

    //set sounds of lose
    lose = new QMediaPlayer();
    lose->setMedia(QUrl("qrc:/sounds/sounds/loser.mp3"));

    //give bone the ability to move
    QTimer * arrow_timer = new QTimer(this);
    connect (arrow_timer, SIGNAL(timeout()), this, SLOT(move()));
    arrow_timer->start(20);
}

void Bone::move()
{
    if (game->pause == 1)
    {
        int step = 20;
        double alpha = rotation();

        double dx = step * qCos(qDegreesToRadians(alpha));
        double dy = step * qSin(qDegreesToRadians(alpha));

        setPos(x()+dx, y()+dy);


        QList<QGraphicsItem*> colliders = collidingItems();
        //find base
        for (int i = 0; i < colliders.size(); ++i)
        {
            if (typeid (*(colliders[i])) == typeid(Base))
            {
                game->base_health->decrease(1);
                game->scene->removeItem(this);
                delete this;
            }
        }
    }

    //if you lose, game will be finished
    if (game->base_health->getHealth() <= 0)
    {
        game->pause = -1;
        lose->play();

        //game over event
        game->reply =
        QMessageBox::question(game, "GAME OVER", "Would you like to try again?",
                              QMessageBox::Yes | QMessageBox::No);

        //ask for restarting the game
        if (game->reply == QMessageBox::No)
        {
            game->close();
        }
        else
        {
            game->scene->clear();
            game->close();
            game = new Game(game->mn);
            game->show();
        }
    }
}
