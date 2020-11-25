#include "UpdateHelper.h"
#include "game.h"

#include "Fireballtower.h"
#include "ArrowTower.h"
#include "Stonetower.h"

#include <QTimer>

extern Game * game;

UpdateHelper::UpdateHelper(upgrade_quality tower_stats, QGraphicsItem* parent) :QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/hammer.png"));
    temp = tower_stats;

    QTimer * two_seconds_for_hammer = new QTimer(this);
    connect (two_seconds_for_hammer, SIGNAL(timeout()), this, SLOT(rebuilder()));
    two_seconds_for_hammer->start(2000);
}

void UpdateHelper::rebuilder()
{
    //pup pup pop pop
    //destroy tower and create upgraded one
    QList <QGraphicsItem *> colliding_items = collidingItems();
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


