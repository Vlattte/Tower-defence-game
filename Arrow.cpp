#include "Arrow.h"
#include "Goblin.h"
#include "Biggoblin.h"
#include "game.h"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

#include <QDebug>

extern Game * game;

Arrow::Arrow(bullet_types arrow_type, QGraphicsItem* parent)
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
   switch(arrow_type)
   {
    case small:
       setPixmap(QPixmap(":/images/images/arrow.png"));
       arrow_damage = 1;
       break;
    case large:
       setPixmap(QPixmap(":/images/images/bigArrow.png"));
       arrow_damage = 2;
       break;
   }
//=============================================================

   QTimer * arrow_timer = new QTimer(this);
   connect (arrow_timer, SIGNAL(timeout()), this, SLOT(move()));
   arrow_timer->start(20);
}

void Arrow::move()
{
    //if arrow is out of screen
    if (this->pos().x() >= 1260 || this->pos().x() <= 10
     || this->pos().y() >= 700 || this->pos().y() <= 10)
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
                if ((typeid(*(colliding_items[i])) == typeid(Goblin)
                     || typeid(*(colliding_items[i])) == typeid(BigGoblin)))
                {
                    //check enemy health
                    if (typeid(*(colliding_items[i])) == typeid(Goblin))
                    {
                        enemy_ptr = dynamic_cast <Goblin*> (colliding_items[i]);
                    }
                    else if (typeid(*(colliding_items[i])) == typeid(BigGoblin))
                    {
                        enemy_ptr = dynamic_cast <BigGoblin*> (colliding_items[i]);
                    }

                    //change enemy's health
                    enemy_ptr->decreaseHealth(arrow_damage);
                    game->chat->addText(QString("enemy takes damage ") + QString::number(arrow_damage));

                    if (enemy_ptr->getHealth() <= 0)
                    {
                        game->scene->removeItem(colliding_items[i]);
                        game->gold->increase(enemy_ptr->gold_for_kill);
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
                        delete enemy_ptr;
                    }
                    game->scene->removeItem(this);

                    //count amount of enemies on scene
                    QList<QGraphicsItem *> list = game->scene->items();
                    int count_enemies = 0;
                    for (int i = 0; i < list.size() - 1; ++i)
                    {
                        if (typeid(*(list[i])) == typeid(Goblin)
                                || typeid(*(list[i])) == typeid(BigGoblin))
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
