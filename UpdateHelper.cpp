#include "UpdateHelper.h"
#include "Towerbuilder.h"
#include "game.h"

#include "Fireballtower.h"
#include "ArrowTower.h"
#include "Stonetower.h"

#include <QTimer>

extern Game * game;

UpdateHelper::UpdateHelper(upgrade_quality tower_stats, bool destroy, QGraphicsItem* parent) :QObject(), QGraphicsPixmapItem(parent)
{
    //set pixmap
    setPixmap(QPixmap(":/images/images/hammer.png"));

    //remember tower stats
    temp = tower_stats;
    is_destroy = destroy;

    //set sounds of tower destroying
    destroy_sound = new QMediaPlayer();
    destroy_sound->setMedia(QUrl("qrc:/sounds/sounds/destroy.wav"));
    destroy_sound->setVolume(40);

    QTimer * two_seconds_for_hammer = new QTimer(this);
    connect (two_seconds_for_hammer, SIGNAL(timeout()), this, SLOT(rebuilder()));
    two_seconds_for_hammer->start(2000);
}

void UpdateHelper::rebuilder()

{
    QList <QGraphicsItem *> colliding_items = collidingItems();
    //pup pup pop pop
    if (is_destroy == true)
    {
        for (int i = 0; i < colliding_items.size(); ++i)
        {
            if (typeid(*(colliding_items[i])) == typeid(ArrowTower) ||
                typeid(*(colliding_items[i])) == typeid(FireBallTower) ||
                typeid(*(colliding_items[i])) == typeid(StoneTower))
            {
                //destroy tower

                //play the sound
                if (destroy_sound->state() == QMediaPlayer::PlayingState)
                {
                    destroy_sound->setPosition(0);
                }
                else if (destroy_sound->state() == QMediaPlayer::StoppedState)
                {
                    destroy_sound->play();
                }

                //remove tower and remember it's position
                QPointF position = colliding_items[i]->pos();
                game->scene->removeItem(colliding_items[i]);
                delete colliding_items[i];

                //build towerbuilder
                int builderX = position.x() + 40;
                int builderY = position.y() + 50;

                TowerBuilder * builder = new TowerBuilder();
                builder->setPos(builderX, builderY);
                game->scene->addItem(builder);

                //destroy hammer
                game->scene->removeItem(this);
                delete this;
            }
        }
    }

    else
    {
        //destroy tower and create upgraded one

        for (int i = 0; i < colliding_items.size(); ++i)
        {
            if (typeid(*(colliding_items[i])) == typeid(ArrowTower))
            {
                QPointF position = colliding_items[i]->pos();
                game->scene->removeItem(colliding_items[i]);
                delete colliding_items[i];

                ArrowTower * tower = new ArrowTower(temp);
                game->scene->addItem(tower);
                tower->setPos(position);

                game->scene->removeItem(this);
                delete this;
            }
            else if (typeid(*(colliding_items[i])) == typeid(FireBallTower))
            {
                QPointF position = colliding_items[i]->pos();
                game->scene->removeItem(colliding_items[i]);
                delete colliding_items[i];

                FireBallTower * tower = new FireBallTower(temp);
                game->scene->addItem(tower);
                tower->setPos(position);

                game->scene->removeItem(this);
                delete this;
            }
            else if (typeid(*(colliding_items[i])) == typeid(StoneTower))
            {
                QPointF position = colliding_items[i]->pos();
                game->scene->removeItem(colliding_items[i]);
                delete colliding_items[i];

                StoneTower * tower = new StoneTower(temp);
                game->scene->addItem(tower);
                tower->setPos(position);

                game->scene->removeItem(this);
                delete this;
            }
        }
    }


}


