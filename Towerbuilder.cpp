#include "Towerbuilder.h"
#include "game.h"
#include "towerchoice.h"

#include "Fireballtower.h"
#include "ArrowTower.h"
#include "Stonetower.h"

#include <QTimer>

extern Game * game;

TowerBuilder::TowerBuilder(QGraphicsItem * parent): QObject(), QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/images/towerBuilder.png"));

    //set sounds
    not_enough_gold = new QMediaPlayer();
    not_enough_gold->setMedia(QUrl("qrc:/sounds/sounds/Not_enough_gold.wav"));

    anger = new QMediaPlayer();
    anger->setMedia(QUrl("qrc:/sounds/sounds/anger.wav"));
    until_anger = 0;
}

void TowerBuilder::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //counting new tower position
    QPointF spawner_center = mapToScene(event->pos());

    QPointF tower_center = QPointF(x()+45, y()+50);
    QLineF line (tower_center,spawner_center);

    if (!game->build && event->button() == Qt::RightButton)
    {
        //change position of the window
        QPointF point = mapToScene(event->pos());
        int windowX = point.x() + 190;
        int windowY = point.y() + 150;

        //set the window
        TowerChoice * window = new TowerChoice();
        window->move(windowX, windowY);
        window->setModal(true);
        window->exec();

        if (game->build != nullptr)
        {
            //set the position for tower
            game->build->setPos(x() + line.dx(), y() + line.dy());
            game->scene->addItem(game->build);

            game->build = nullptr;

            //delete this tower builder
            game->scene->removeItem(this);

            delete this;
        }
        else
        {
            window->close();
        }
    }

    if (/*!game->build && */ event->button() == Qt::LeftButton)
    {
        if(game->gold->getGold() >= 200)
        {
                 game->chat->addText("Simple tower was built, my Lord");

                 ArrowTower * tower = new ArrowTower();
                 game->gold->decrease(200);

                 //set the position for tower
                 tower->setPos(x() + line.dx(), y() + line.dy());
                 game->scene->addItem(tower);

//                 game->build = nullptr;

                 //delete this tower builder
                 game->scene->removeItem(this);

                 delete this;
        }
        else
        {
            game->chat->addText("Not enough gold for simple tower, my Lord!");
            until_anger++;

            if (until_anger == 5 && game->was_i_already_angry == false)
            {
                //take pause for anger

                game->pause = -1;

                //speak out your feelings
                anger->play();

                QTimer * anger_timer = new QTimer();
                anger_timer->setInterval(anger->duration()); //duration of anger sound


                anger_timer->setSingleShot(true); //it will not repeat
                connect (anger_timer, SIGNAL(timeout()), this, SLOT(turnGameON()));

                anger_timer->start();
            }

            //sound of lake of gold
            if (not_enough_gold->state() == QMediaPlayer::PlayingState)
            {
                not_enough_gold->setPosition(0);
            }
            else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
            {
                not_enough_gold->play();
            }

        }
    }

}

void TowerBuilder::turnGameON()
{
    game->pause = 1;
    game->was_i_already_angry = true;
}

