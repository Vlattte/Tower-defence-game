#include "Arrow.h"
#include "Goblin.h"
#include "Biggoblin.h"
#include "Skeleton.h"
#include "game.h"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

#include <QMessageBox>
#include <QDebug>

extern Game * game;

Arrow::Arrow(bullet_types arrow_type, QGraphicsItem* parent)
{
//========================set=sounds===========================
    enemy_death_sound = new QMediaPlayer();
    enemy_death_sound->setVolume(40);

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

void Arrow::play_death_sound(Enemy *enemy_ptr)
{
    /////////////////////////////////////////////////////////////////////////////////
    if (typeid(*(enemy_ptr)) == typeid(Goblin))
    {
        //sound of goblin's death
        enemy_death_sound->setMedia(QUrl("qrc:/sounds/sounds/goblin_dead.wav"));
    }
    else if (typeid(*(enemy_ptr)) == typeid(BigGoblin))
    {
        //sound of big goblin's death
        enemy_death_sound->setMedia(QUrl("qrc:/sounds/sounds/big_goblin_death.wav"));
    }
    else if (typeid(*(enemy_ptr)) == typeid(Skeleton))
    {
        //sound of skeleton's death
        enemy_death_sound->setMedia(QUrl("qrc:/sounds/sounds/skeleton_death.wav"));
    }
    /////////////////////////////////////////////////////////////////////////////////

    //play the sound
    if (enemy_death_sound->state() == QMediaPlayer::PlayingState)
    {
        enemy_death_sound->setPosition(0);
    }
    else if (enemy_death_sound->state() == QMediaPlayer::StoppedState)
    {
        enemy_death_sound->play();
    }
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
                if ((typeid(*(colliding_items[i])) == typeid(Goblin) ||
                     typeid(*(colliding_items[i])) == typeid(BigGoblin)) ||
                     typeid(*(colliding_items[i])) == typeid(Skeleton))
                {
                    //check type of enemy and his health
                    if (typeid(*(colliding_items[i])) == typeid(Goblin))
                    {
                        enemy_ptr = dynamic_cast <Goblin*> (colliding_items[i]);
                    }
                    else if (typeid(*(colliding_items[i])) == typeid(BigGoblin))
                    {
                        enemy_ptr = dynamic_cast <BigGoblin*> (colliding_items[i]);
                    }
                    else if (typeid(*(colliding_items[i])) == typeid(Skeleton))
                    {
                        enemy_ptr = dynamic_cast <Skeleton*> (colliding_items[i]);
                    }

                    if (colliding_items[i]->scene())
                    {
                        //change enemy's health
                        enemy_ptr->decreaseHealth(arrow_damage);
                        game->chat->addText(QString("enemy takes damage ") + QString::number(arrow_damage));

                        if (enemy_ptr->getHealth() <= 0)
                        {
                            //increase gold and remove enemy from scene
                            if (colliding_items[i]->scene())
                                game->scene->removeItem(colliding_items[i]);
                            game->gold->increase(enemy_ptr->gold_for_kill);

                            play_death_sound(enemy_ptr);

                            //clear memory
                            if (enemy_ptr)
                                delete enemy_ptr;
                        }
                        game->scene->removeItem(this);

                        //count amount of enemies on scene
                        QList<QGraphicsItem *> list = game->scene->items();
                        int count_enemies = 0;
                        for (int i = 0; i < list.size() - 1; ++i)
                        {
                            if (typeid(*(list[i])) == typeid(Goblin) ||
                                typeid(*(list[i])) == typeid(BigGoblin) ||
                                typeid(*(list[i])) == typeid(Skeleton))
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

                                //restart window
                                game->reply =
                                QMessageBox::question(game, "Victory!", "Would you like to win again?",
                                                      QMessageBox::Yes | QMessageBox::No);

                                //ask for restarting the game
                                if (game->reply == QMessageBox::No)
                                {
                                    game->scene->clear();
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
}
