#include "Enemy.h"
#include "Base.h"
#include "game.h"
#include "mainwindow.h"

extern Game * game;
extern MainWindow * window;

#include <QPointF>
#include <QLineF>
#include <QVector>
#include <QPixmap>
#include <qmath.h>
#include <QTimer>
#include <QMessageBox>


Enemy::Enemy(QGraphicsItem* parent)
{
    //========================set=sounds==========================
    goblin_pain = new QMediaPlayer();
    goblin_pain->setMedia(QUrl("qrc:/sounds/sounds/goblin_pain.wav"));
    goblin_pain->setVolume(20);

    //set sounds of victory
    victory = new QMediaPlayer();
    victory->setMedia(QUrl("qrc:/sounds/sounds/its_victory.mp3"));

    //set sounds of lose
    lose = new QMediaPlayer();
    lose->setMedia(QUrl("qrc:/sounds/sounds/loser.mp3"));
    //============================================================
    enemy_health = 3;

    //================set=the=picture=of=the=enemy================
    setPixmap(QPixmap(":/images/images/goblin.png"));
    //============================================================

    //===============show=health=of=enemy=above=his=head==========
    health_label->setText(QString::number(enemy_health));
    health_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    health_label->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    QPointF position = mapToScene(pos());
    int labelX = position.x() + 25;
    int labelY = position.y() - 10;
    health_label->move(labelX, labelY);
    //============================================================

    //====================rotate=to=the=point=====================
    chooseWay();

    if (random_dest == 1)
    {
       FP.a = {500, 205};
       FP.b = {520, 230};
       FP.c = {715, 230};
       FP.d = {785, 270};
       FP.e = {790, 275};
       FP.f = {795, 278};
       FP.g = {795, 490};
       FP.h = {999, 490};
       FP.i = {1000, 490};
    }
    else
    {
        FP.a = {500, 160};
        FP.b = {510, 130};
        FP.c = {530, 110};
        FP.d = {550, 90};
        FP.e = {600, 65};
        FP.f = {990, 65};
        FP.g = {1035, 95};
        FP.h = {1070, 150};
        FP.i = {1070, 500};
    }

    if (way_num == 1)
    {
        setPos(0, 100);
        list_of_points << QPoint(80,100) << QPoint(155, 140) << QPoint(420,140)
                       << QPoint(485, 175) << FP.a << FP.b << FP.c << FP.d << FP.e << FP.f
                       << FP.g << FP.h << FP.i << QPoint(1080, 510) << QPoint(1240, 510);
    }
    else if (way_num == 2)
    {
        setPos(0, 415);
        list_of_points << QPoint (0, 430) << QPoint (75, 480) << QPoint (400, 480)
                       << QPoint (475, 510) << QPoint (1240, 510);
    }
    point_index = 0;
    destination = list_of_points[0];
    rotate(destination);
    //============================================================

    //=====================make=the=enemy=move====================
    QTimer * move_timer = new QTimer(this);
    connect (move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(100);
    //============================================================
}

void Enemy::rotate(QPointF point)
{
    QLineF line(pos(),point);
    setRotation(-1 * line.angle());
}

void Enemy::decreaseHealth(int damage)
{
    enemy_health -= damage;
    health_label->setText(QString::number(enemy_health));

    //sound of goblins death
    if (goblin_pain->state() == QMediaPlayer::PlayingState)
    {
        goblin_pain->setPosition(0);
    }
    else if (goblin_pain->state() == QMediaPlayer::StoppedState)
    {
        goblin_pain->play();
    }
}

int Enemy::getHealth() const
{
    return enemy_health;
}

void Enemy::chooseWay()
{
    //================random=enemy=move=======================
    int lowest = 1, highest = 2;
    int range = (highest-lowest) + 1;
    random_dest = lowest + int(range * (rand() / (RAND_MAX + 1.0)));
    way_num = lowest + int(range * (rand() / (RAND_MAX + 1.0)));
    //========================================================
}

void Enemy::move()
{
    if (game->pause == 1)
    {
        //-------------------moving process-----------------------
            QLineF line (QPointF(pos()), destination);
            if (line.length() < 10)
            {
                point_index++;
                if(point_index >= list_of_points.size())
                {
                    return;
                }
                destination = list_of_points[point_index];
                rotate(destination);
            }

            int step = 10;
            double alpha = rotation();

            double dx = step * qCos(qDegreesToRadians(alpha));
            double dy = step * qSin(qDegreesToRadians(alpha));

            setPos(x()+dx, y()+dy);

            QPointF position = mapToScene(pos());
            int labelX = position.x() + 25;
            int labelY = position.y() - 10;
            health_label->move(labelX, labelY);
        //---------------------------------------------------------

        //kill the enemy and decrease base's health if they collide
            QList <QGraphicsItem *> colliding_items = collidingItems();
            for (int i = 0; i < colliding_items.size(); ++i)
            {
                if (typeid(*(colliding_items[i])) == typeid(Base))
                {
                    game->scene->removeItem(this);
                    game->base_health->decrease(10);

                    QList<QGraphicsItem *> list = game->scene->items();
                    int count_enemies = 0;
                    for (int i = 0; i < list.size() - 1; ++i)
                    {
                        if (typeid(*(list[i])) == typeid(Enemy))
                        {
                            count_enemies++;
                        }
                    }

                    //if you lose, game will be finished
                    if (game->base_health->getHealth() <= 0)
                    {
                        game->pause = -1;
                        lose->play();

                        //game over event
                        QMessageBox::StandardButton reply =
                        QMessageBox::question(game, "GAME OVER", "Would you like to try again?", QMessageBox::Yes | QMessageBox::No);

                        //ask for restarting the game
                        if (reply == QMessageBox::No)
                        {
                            game->close();
                        }
                        else
                        {
                            game->close();
                            game = new Game();
                            game->show();
                        }
                    }

                    //if there are not enemies on scene
                    if (count_enemies == 0 && game->spawn_number[game->index] <=0)
                    {
                        if (game->index == 3)
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

                    //clear memory
                    delete health_label;
                    delete this;
                }
            }
        //---------------------------------------------------------

    }
}

void Enemy::closing()
{
    game->close();
}
