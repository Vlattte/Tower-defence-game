#include "Stonebullet.h"
#include "Enemy.h"
#include "game.h"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

#include <QDebug>

extern Game * game;

StoneBullet::StoneBullet(bullet_types stone_type, QGraphicsItem* parent)
{
//========================set=sounds===========================
    goblin_dead = new QMediaPlayer();
    goblin_dead->setMedia(QUrl("qrc:/sounds/sounds/goblin_dead.wav"));
    goblin_dead->setVolume(40);

    //set sounds of victory
    victory = new QMediaPlayer();
    victory->setMedia(QUrl("qrc:/sounds/sounds/its_victory.mp3"));

//=============================================================

//========================set=the=arrow========================
   switch(stone_type)
   {
    case small:
       setPixmap(QPixmap(":/images/images/stone_bullet.png"));
       stone_damage = 2;
       break;
    case large:
       setPixmap(QPixmap(":/images/big_stone_bullet.png"));
       stone_damage = 3;
       break;
   }
//=============================================================

   QTimer * stone_timer = new QTimer(this);
   connect (stone_timer, SIGNAL(timeout()), this, SLOT(move()));
   stone_timer->start(20);
}

void StoneBullet::move()
{
    //if arrow is out of screen
    if (this->pos().x() >= 1280 || this->pos().x() <= 0
     || this->pos().y() >= 720 || this->pos().y() <= 0)
    {
        game->scene->removeItem(this);
        delete this;
    }
    else{
        if (game->pause == 1)
        {
            int step = 20;
            double alpha = rotation();

            double dx = step * qCos(qDegreesToRadians(alpha));
            double dy = step * qSin(qDegreesToRadians(alpha));

            setPos(x()+dx, y()+dy);

            //kill the enemy and the bullet if they collide
            QList <QGraphicsItem *> colliding_items = collidingItems();
            for (int i = 0; i < colliding_items.size(); ++i)
            {
                if (typeid(*(colliding_items[i])) == typeid(Enemy))
                {
                    //check enemy health
                    enemy_ptr = dynamic_cast <Enemy*> (colliding_items[i]);

                    //change enemy's health
                    enemy_ptr->decreaseHealth(stone_damage);
                    game->chat->addText(QString("enemy takes damage ") + QString::number(stone_damage));

                    if (enemy_ptr->getHealth() <= 0)
                    {
                        game->scene->removeItem(colliding_items[i]);
                        game->gold->increase(100);
                        game->chat->addText("Enemy was killed, HAAAAAAAAA");

                        //sound of goblin's death
                        if (goblin_dead->state() == QMediaPlayer::PlayingState)
                        {
                            goblin_dead->setPosition(0);
                        }
                        else if (goblin_dead->state() == QMediaPlayer::StoppedState)
                        {
                            goblin_dead->play();
                        }

                        //clear memory
                        enemy_ptr = nullptr;
                        delete enemy_ptr;

                        delete colliding_items[i];
                    }
                    game->scene->removeItem(this);

                    //count amount of enemies on scene
                    QList<QGraphicsItem *> list = game->scene->items();
                    int count_enemies = 0;
                    for (int i = 0; i < list.size() - 1; ++i)
                    {
                        if (typeid(*(list[i])) == typeid(Enemy))
                        {
                            count_enemies++;
                        }
                    }

                    //if there are not enemies on scene
                    if (count_enemies == 0 && game->spawn_number[game->index] <=0)
                    {
                        if(game->index == 3)
                        {
                            game->pause = -1;
                            victory->play();
                            game->chat->addText("You killed anyone!");
                            game->chat->addText("You are the best!!");
                            game->chat->addText("You saved all of us!!!");
                            game->chat->addText("Thank you for playing this game <3");
                        }
                        else
                        {
                            game->wave_change_ability = true;
                        }
                    }

                    delete this;

                                  }
            }
        }
    }
}
