#include "game.h"
#include "Arrow.h"
#include "ArrowTower.h"
#include "Tower.h"
#include "Goblin.h"
#include "Biggoblin.h"
#include "Skeleton.h"
#include "Towerbuilder.h"
#include "Base.h"
#include "Health.h"
#include "gold.h"
#include "InfoIcon.h"
#include "Pausebutton.h"


#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QMessageBox>

extern int pause;

Game::Game(number_of_map map_num) : QGraphicsView()
{  
    //set map settings
    settings.set_varieties(map_num);
    mn = map_num;

    //create and set the scene
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0 , 0, 1280, 720);
    setFixedSize(1280, 720);

    //unable scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //set background picture
    setBackgroundBrush(QBrush(QImage(settings.variety.map_name)));

    ///////////////////////////////////////////////
    //its useless, might be used in future updates
    cursor = nullptr;
    build = nullptr;
    setMouseTracking(true);
    ///////////////////////////////////////////////

    //add the base
    Base *base = new Base();
    base->setPos(settings.variety.base_point);
    scene->addItem(base);

    //add info icon
    InfoIcon * info = new InfoIcon();
    scene->addItem(info);
    info->setPos(1200,600);

    //add pause button
    PauseButton * pause_button = new PauseButton();
    scene->addItem(pause_button);
    pause_button->setPos(1200, 650);

    //add base's health
    base_health->setPos(0, 0);
    scene->addItem(base_health);

    //add gold counter
    gold->setPos(1100, 0);
    scene->addItem(gold);

    //add image of coin
    QImage image(":/images/images/coin.png");
    QGraphicsPixmapItem* coin = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    coin->setPos(1080, 5);
    scene->addItem(coin);

    //add chat
    chat->setPos(470, 600);
    scene->addItem(chat);

    //add the builders
    TowerBuilder *builder0  = new TowerBuilder(),
                     *builder1 = new TowerBuilder(),
                     *builder2 = new TowerBuilder(),
                     *builder3 = new TowerBuilder(),
                     *builder4 = new TowerBuilder(),
                     *builder5 = new TowerBuilder(),
                     *builder6 = new TowerBuilder(),
                     *builder7 = new TowerBuilder(),
                     *builder8 = new TowerBuilder(),
                     *builder9 = new TowerBuilder();

        builder0->setPos(settings.variety.tbp[0]);
        scene->addItem(builder0);
        builder1->setPos(settings.variety.tbp[1]);
        scene->addItem(builder1);
        builder2->setPos(settings.variety.tbp[2]);
        scene->addItem(builder2);
        builder3->setPos(settings.variety.tbp[3]);
        scene->addItem(builder3);
        builder4->setPos(settings.variety.tbp[4]);
        scene->addItem(builder4);
        builder5->setPos(settings.variety.tbp[5]);
        scene->addItem(builder5);
        builder6->setPos(settings.variety.tbp[6]);
        scene->addItem(builder6);
        builder7->setPos(settings.variety.tbp[7]);
        scene->addItem(builder7);
        builder8->setPos(settings.variety.tbp[8]);
        scene->addItem(builder8);
        builder9->setPos(settings.variety.tbp[9]);
        scene->addItem(builder9);


//    TowerBuilder** builder = new TowerBuilder*[10];

//    for (int i = 0; i < 10; ++i)
//    {
//        builder[i]->setPos(settings.variety.tbp[i]);
//        scene->addItem(builder[i]);
//    }


    //addition(easter egg)
    was_i_already_angry = false;
    //========

    //set spawn numbers
    wave_change_ability = false;
    index = 0;

    while (index < 4)
    {
        spawn_number[index] = 10 + 5 * index;
        ++index;
    }
    index = 0;

    //spawn enemies
    QTimer * enemySpawnTimer = new QTimer();
    QObject::connect(enemySpawnTimer, SIGNAL(timeout()), this, SLOT(spawn_simple_enemy()) );
    enemySpawnTimer->start(2500);
}

void Game::changeCursor(QString filename)
{
    if (cursor)
    {
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if (cursor)
    {
        cursor->setPos(event->pos());
    }
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
    {
        pause = pause * -1;
    }
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
}

void Game::spawn_simple_enemy()
{
    if(pause == 1)
    {
        //spawn enemies
        if (spawn_number[index] > 0)
        {
            //every fifth enemy is Big Goblin
            if (index > 1 && (spawn_number[index] % 5) == 0)
            {
                //spawning of big Goblin
                BigGoblin * goblin = new BigGoblin();
                scene->addItem(goblin);
                spawn_number[index]--;
            }
            else if (index > 0 && (spawn_number[index] % 3) == 0)
            {
                Skeleton * skeletonchik = new Skeleton();
                scene->addItem(skeletonchik);
                spawn_number[index]--;
            }
            else
            {
                Goblin * enemy = new Goblin();
                scene->addItem(enemy);
                spawn_number[index]--;
            }
        }

        //change wave
        if (index != 3)
        {
            if (spawn_number[index] == 0 && wave_change_ability == true)
            {
                QMessageBox::about(this, "Wave " + QString::number(index + 1),
                           "Wave " + QString::number(index + 1) + " was done");
                index++;
                wave_change_ability = false;
            }
        }
    }
}





