#include "game.h"
#include "Arrow.h"
#include "ArrowTower.h"
#include "Tower.h"
#include "Enemy.h"
#include "Towerbuilder.h"
#include "Base.h"
#include "Health.h"
#include "gold.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QTime>
#include <QMediaPlayer>
#include <QMessageBox>

extern int pause;

Game::Game() : QGraphicsView()
{  
    //create and set the scene
    scene = new QGraphicsScene();
    setScene(scene);
    scene->setSceneRect(0 , 0, 1280, 720);
    setFixedSize(1280, 720);

    //unable scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setBackgroundBrush(QBrush(QImage(":/images/images/lvl_one_background")));

    cursor = nullptr;
    build = nullptr;
    setMouseTracking(true);

    //add the base
    Base *base = new Base();
    base->setPos(1180, 490);
    scene->addItem(base);

    //add base's health
    base_health->setPos(0, 0);
    scene->addItem(base_health);

    //add gold counter
    gold->setPos(1100, 0);
    scene->addItem(gold);

    QImage image(":/images/images/coin.png");
    QGraphicsPixmapItem* coin = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    coin->setPos(1080, 5);
    scene->addItem(coin);

    //add chat
    chat->setPos(470, 600);
    scene->addItem(chat);

    //add the builder
    TowerBuilder *builder  = new TowerBuilder(),
                 *builder1 = new TowerBuilder(),
                 *builder2 = new TowerBuilder(),
                 *builder3 = new TowerBuilder(),
                 *builder4 = new TowerBuilder(),
                 *builder5 = new TowerBuilder(),
                 *builder6 = new TowerBuilder(),
                 *builder7 = new TowerBuilder(),
                 *builder8 = new TowerBuilder(),
                 *builder9 = new TowerBuilder();

    builder->setPos(660, 400);
    scene->addItem(builder);
    builder1->setPos(340, 75);
    scene->addItem(builder1);
    builder2->setPos(600, 190);
    scene->addItem(builder2);
    builder3->setPos(900, 200);
    scene->addItem(builder3);
    builder4->setPos(900, 410);
    scene->addItem(builder4);
    builder5->setPos(55, 240);
    scene->addItem(builder5);
    builder6->setPos(360, 250);
    scene->addItem(builder6);
    builder7->setPos(210, 425);
    scene->addItem(builder7);
    builder8->setPos(1150, 410);
    scene->addItem(builder8);
    builder9->setPos(1150, 200);
    scene->addItem(builder9);

    //addition
    was_i_already_angry = false;
    //========

    //set spawn numbers
    wave_change_ability = false;
    index = 0;

    while (index < 4)
    {
        spawn_number[index] = 1 /*+ 1 * index*/;
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
}

void Game::spawn_simple_enemy()
{
    if(pause == 1)
    {
        //spawn enemies
        if (spawn_number[index] > 0)
        {
            Enemy * enemy = new Enemy();
            scene->addItem(enemy);
            spawn_number[index]--;
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





