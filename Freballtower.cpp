#include <QGraphicsItem>
#include <QPixmap>
#include <QPolygonF>
#include <QVector>
#include <QPointF>
#include <QLineF>
#include <QTimer>

#include "Towerupgrade.h"
#include "Fireballtower.h"
#include "Fireball.h"
#include "game.h"


extern Game * game;

FireBallTower::FireBallTower(upgrade_quality temp, QGraphicsItem* parent)
{
    //============================set=sounds==================================
        fire_sound = new QMediaPlayer();
        fire_sound->setMedia(QUrl("qrc:/sounds/sounds/Fireball.wav"));
    //========================================================================

    //================set=normal=settings=for=tower's=upgrades================
        Fireballtower.bullet_size = temp.bullet_size;
        Fireballtower.shooting_range = temp.shooting_range;
        Fireballtower.shooting_speed = temp.shooting_speed;
        Fireballtower.num = temp.num;
        Fireballtower.is_upgraded = temp.is_upgraded;

        QString picName;
        if (Fireballtower.num == speed)
        {
            picName = ":/images/images/fireball_tower_speeded_up.png";
        }
        //if no picture in picname, use default
        if (Fireballtower.num == none)
        {
            picName = ":/images/images/fireball_tower.png";
        }
    //========================================================================
        //set the picture of the tower
        setPixmap(QPixmap(picName));

    //--------------------------atack_area_as_a_polygon---------------------------
        //creating atack area
        QVector<QPointF> points;
        points << QPoint(1, 0) << QPoint(2, 0) << QPoint(3, 1) << QPoint(3, 2)
               << QPoint(2, 3) << QPoint(1, 3) << QPoint(0, 2) << QPoint(0 ,1);

        int increaser = Fireballtower.shooting_range;
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

            shoot_timer->start(Fireballtower.shooting_speed);
        }
}

double FireBallTower::distanseBetweenItems(QGraphicsItem *item)
{
    QLineF line (pos(), item->pos());
    return line.length();
}

void FireBallTower::shoot()
{
    if (game->pause == 1)
    {
        //make an arrow and rotate to the target
        FireBall * fireball = new FireBall(Fireballtower.bullet_size);
        fireball->setPos(x()+45, y()+50);
        QLineF line(QPointF(x(), y()), QPointF(target.x(), target.y()));

        double angle = (-1) * line.angle();
        fireball->setRotation(angle);

        game->scene->addItem(fireball);

        //sound of shooting
        if (fire_sound->state() == QMediaPlayer::PlayingState)
        {
            fire_sound->setPosition(0);
        }
        else if (fire_sound->state() == QMediaPlayer::StoppedState)
        {
            fire_sound->play();
        }
    }
}

void FireBallTower::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        //change position of the window
        QPointF point = mapToScene(event->pos());
        int windowX = point.x() + 190;
        int windowY = point.y() + 90;

        //set the window
        TowerUpgrade window(Fireballtower);
        window.move(windowX, windowY);
        window.setModal(true);
        window.exec();
    }
}

void FireBallTower::aquire()
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
