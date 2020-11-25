#include "ArrowTower.h"
#include "Arrow.h"
#include "game.h"
#include "Enemy.h"
#include "Towerupgrade.h"

#include <QGraphicsItem>
#include <QPixmap>
#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QTimer>

#include <QDebug>

extern Game * game;


ArrowTower::ArrowTower(upgrade_quality temp, QGraphicsItem* parent): QObject(), MainTower()
{
//============================set=sounds==================================
    arrow_sound = new QMediaPlayer();
    arrow_sound->setMedia(QUrl("qrc:/sounds/sounds/arrow_shot.wav"));
//========================================================================

//================set=normal=settings=for=tower's=upgrades================
    simpleTower.bullet_size = temp.bullet_size;
    simpleTower.shooting_range = temp.shooting_range;
    simpleTower.shooting_speed = temp.shooting_speed;
//========================================================================
    //set the picture of the tower
    setPixmap(QPixmap(":/images/images/New_tower.png"));

//--------------------------atack_area_as_a_polygon---------------------------
    //creating atack area
    QVector<QPointF> points;
    points << QPoint(1, 0) << QPoint(2, 0) << QPoint(3, 1) << QPoint(3, 2)
           << QPoint(2, 3) << QPoint(1, 3) << QPoint(0, 2) << QPoint(0 ,1);

    int increaser = simpleTower.shooting_range;
    for (int i = 0; i < points.size(); ++i)
    {
        points[i] *= increaser;
    }

    QPolygonF p(points);
    atack_area = new QGraphicsPolygonItem(p, this);
    atack_area->setPen(QPen(Qt::DotLine));

    //match centres
    QPointF poly_center(1.5, 1.5);
    poly_center *= increaser;
    poly_center = mapToScene(poly_center);

    QPointF tower_center (x()+45, y()+50);
    QLineF line (poly_center, tower_center);

    atack_area->setPos(x()+line.dx(), y()+line.dy());
 //----------------------------------------------------------------------------

    if (game->pause == 1)
    {
        //shooting
        QTimer * shoot_timer = new QTimer();
        connect(shoot_timer, SIGNAL(timeout()), this, SLOT(aquire()));

        shoot_timer->start(simpleTower.shooting_speed);
    }
}

double ArrowTower::distanseBetweenItems(QGraphicsItem *item)
{
    QLineF line (pos(), item->pos());
    return line.length();
}

void ArrowTower::shoot()
{
    if (game->pause == 1)
    {
        //make an arrow and rotate to the target
        Arrow * arrow = new Arrow(simpleTower.bullet_size);
        arrow->setPos(x()+45, y()+50);
        QLineF line(QPointF(x(), y()), QPointF(target.x(), target.y()));

        double angle = (-1) * line.angle();
        arrow->setRotation(angle);

        game->scene->addItem(arrow);

        //sound of shooting
        if (arrow_sound->state() == QMediaPlayer::PlayingState)
        {
            arrow_sound->setPosition(0);
        }
        else if (arrow_sound->state() == QMediaPlayer::StoppedState)
        {
            arrow_sound->play();
        }
    }
}

void ArrowTower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     if (event->button() == Qt::RightButton)
     {
         //change position of the window
         QPointF point = mapToScene(event->pos());
         int windowX = point.x() + 190;
         int windowY = point.y() + 90;

         //set the window
         TowerUpgrade window(simpleTower);
         window.move(windowX, windowY);
         window.setModal(true);
         window.exec();
     }
}

void ArrowTower::aquire()
{
    QList <QGraphicsItem *> colliders = atack_area->collidingItems();
    has_target = false;

    //if the tower is the only collider
    if (colliders.size() == 1)
    {
        has_target = false;
        return;
    }
    else{
    double closest_target = 300;
    QPointF closest_point = QPointF(0, 0);

    for(int i = 0; i < colliders.size(); ++i)
    {
        Enemy * enemy_check = dynamic_cast<Enemy*>(colliders[i]);
        if (enemy_check)
        {
            double distToEnemy = distanseBetweenItems(enemy_check);
            if (closest_target > distToEnemy)
            {
                closest_target = distToEnemy;
                closest_point = colliders[i]->pos();
                has_target = true;
            }
        }
    }
    if (has_target == true)
    {
        target = closest_point;
        shoot();
    }
    }
}
