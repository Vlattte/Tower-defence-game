#ifndef FIREBALLTOWER_H
#define FIREBALLTOWER_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPointF>
#include <QObject>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>

#include "Upgrades.h"
#include "Tower.h"

class FireBallTower: public QObject, public MainTower
{
    Q_OBJECT
public:
    FireBallTower(upgrade_quality temp = {1300, 60, small, none}, QGraphicsItem* parent = 0);
    virtual double distanseBetweenItems(QGraphicsItem * item);
    void shoot();

    void mousePressEvent (QGraphicsSceneMouseEvent * event);
    bool is_any_upgrades();
public slots:
    void aquire();

private:
    QGraphicsPolygonItem * atack_area;
    QPointF target = QPointF(0, 0);

    bool has_target;
    QMediaPlayer * fire_sound;
    upgrade_quality Fireballtower;
};

#endif // FIREBALLTOWER_H
