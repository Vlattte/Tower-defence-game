#ifndef ARROWTOWER_H
#define ARROWTOWER_H

#include "Tower.h"
#include "Upgrades.h"
#include "Fireballtower.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QGraphicsPolygonItem>
#include <QPointF>
#include <QObject>
#include <QList>
#include <QGraphicsSceneMouseEvent>
#include <QMediaPlayer>

#include "Towerupgrade.h"


class ArrowTower: public QObject, public MainTower
{
    Q_OBJECT
public:
    ArrowTower(upgrade_quality temp = {1100, 80, small, 100, none}, QGraphicsItem* parent = 0);
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
    QMediaPlayer * arrow_sound;
    upgrade_quality simpleTower;

    TowerUpgrade *window;
};

#endif // ARROWTOWER_H
