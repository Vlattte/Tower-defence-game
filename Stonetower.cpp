#include <QGraphicsItem>
#include <QPixmap>
#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QTimer>

#include "Towerupgrade.h"
#include "Stonetower.h"
#include "Stonebullet.h"
#include "game.h"
#include "Goblin.h"
#include "Biggoblin.h"
#include "Skeleton.h"


extern Game * game;

StoneTower::StoneTower(upgrade_quality temp, QGraphicsItem* parent)
{
    //============================set=sounds==================================
        stone_sound = new QMediaPlayer();
        stone_sound->setMedia(QUrl("qrc:/sounds/sounds/stone_bullet.wav"));
    //========================================================================

    //================set=normal=settings=for=tower's=upgrades================
        stonetower.bullet_size = temp.bullet_size;
        stonetower.shooting_range = temp.shooting_range;
        stonetower.shooting_speed = temp.shooting_speed;
        stonetower.num = temp.num;
        stonetower.is_upgraded = temp.is_upgraded;
        stonetower.tower_price = temp.tower_price;

        QString picName;
        if (stonetower.num == speed)
        {
            picName = ":/images/images/stone_tower_speeded_up.png";
        }
        //if no picture in picname, use default
        if (stonetower.num == none)
        {
            picName = ":/images/images/stone_tower.png";
        }
    //========================================================================
        //set the picture of the tower
        setPixmap(QPixmap(picName));

    //--------------------------atack_area_as_a_polygon---------------------------
        //creating atack area
        QVector<QPointF> points;
        points << QPoint(1, 0) << QPoint(2, 0) << QPoint(3, 1) << QPoint(3, 2)
               << QPoint(2, 3) << QPoint(1, 3) << QPoint(0, 2) << QPoint(0 ,1);

        int increaser = stonetower.shooting_range;
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

        QPointF tower_center (x()+35, y()+48);
        QLineF line (poly_center, tower_center);

        atack_area->setPos(x()+line.dx(), y()+line.dy());
     //----------------------------------------------------------------------------

        if (game->pause == 1)
        {
            //shooting
            QTimer * shoot_timer = new QTimer();
            connect(shoot_timer, SIGNAL(timeout()), this, SLOT(aquire()));

            shoot_timer->start(stonetower.shooting_speed);
        }
}

double StoneTower::distanseBetweenItems(QGraphicsItem *item)
{
    QLineF line (pos(), item->pos());
    return line.length();
}

void StoneTower::shoot()
{
    if (game->pause == 1)
    {
        //make an arrow and rotate to the target
        StoneBullet * stone = new StoneBullet(stonetower.bullet_size);
        stone->setPos(x()+45, y()+50);
        QLineF line(QPointF(x(), y()), QPointF(target.x(), target.y()));

        double angle = (-1) * line.angle();
        stone->setRotation(angle);

        game->scene->addItem(stone);

        //sound of shooting
        if (stone_sound->state() == QMediaPlayer::PlayingState)
        {
            stone_sound->setPosition(0);
        }
        else if (stone_sound->state() == QMediaPlayer::StoppedState)
        {
            stone_sound->play();
        }
    }
}

void StoneTower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (!is_any_upgrades())
    {
        if (event->button() == Qt::RightButton)
        {
            //change position of the window
            QPointF point = mapToScene(event->pos());
            int windowX = point.x() + 190;
            int windowY = point.y() + 90;

            //set the window
            TowerUpgrade window(stonetower);
            window.move(windowX, windowY);
            window.setModal(true);
            window.exec();
        }
    }
}

bool StoneTower::is_any_upgrades()
{
    return (stonetower.is_upgraded.bullet_size    &&
            stonetower.is_upgraded.shooting_range &&
            stonetower.is_upgraded.shooting_speed);
}

void StoneTower::aquire()
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
        target = closest_point;
        shoot();
    }
    }
}
