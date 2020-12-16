#include "ArrowTower.h"
#include "Arrow.h"
#include "game.h"
#include "Goblin.h"
#include "Biggoblin.h"
#include "Skeleton.h"
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
    simpleTower.num = temp.num;
    simpleTower.is_upgraded = temp.is_upgraded;
    simpleTower.tower_price = temp.tower_price;

    QString picName;

    if (simpleTower.num == speed)
    {
        picName = ":/images/images/archer_tower_speeded_up.png";
    }
    //if no picture in picname, use default
    else if (simpleTower.num == none)
    {
        picName = ":/images/images/archer_tower.png";
    }
//========================================================================
    //set the picture of the tower
    setPixmap(QPixmap(picName));

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
    if (!is_any_upgrades())
    {
        if (event->button() == Qt::RightButton)
        {
            //change position of the window
            QPointF p = mapToScene(event->pos());
            int windowX = p.x() + 190;
            int windowY = p.y() + 90;

            //if clicked on tower
            if (event->button() == Qt::LeftButton
             || event->button() == Qt::RightButton)
            {
                QPointF point = event->scenePos();
                if(!this->sceneBoundingRect().intersects(QRectF(point.x(), point.y(), 1, 1))){
                    event->ignore();
                    return;
                }
            }

            //set the window
            window = new TowerUpgrade(simpleTower);
            window->move(windowX, windowY);
            window->setModal(true);
            window->exec();
        }
    }
}

bool ArrowTower::is_any_upgrades()
{
    return (simpleTower.is_upgraded.bullet_size    &&
            simpleTower.is_upgraded.shooting_range &&
            simpleTower.is_upgraded.shooting_speed);
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
    else
    {
        double closest_target = 300;
        QPointF closest_point = QPointF(0, 0);

        for(int i = 0; i < colliders.size(); ++i)
        {

            Enemy * enemy_check;

            if (typeid (*(colliders[i])) == typeid(Goblin))
                enemy_check = dynamic_cast<Goblin*>(colliders[i]);
            else if (typeid (*(colliders[i])) == typeid(BigGoblin))
                enemy_check = dynamic_cast<BigGoblin*>(colliders[i]);
            else if (typeid (*(colliders[i])) == typeid(Skeleton))
                enemy_check = dynamic_cast<Skeleton*>(colliders[i]);
            else
                enemy_check = nullptr;

            if (enemy_check != nullptr)
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
            int pointX =  closest_point.x() - 15;
            int pointY =  closest_point.y() - 10;
            closest_point = QPointF(pointX, pointY);

            target = closest_point;
            shoot();
        }
    }
}
