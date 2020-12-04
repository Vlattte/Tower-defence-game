#ifndef STONETOWER_H
#define STONETOWER_H


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

class StoneTower: public QObject, public MainTower
{
    Q_OBJECT
public:
    StoneTower(upgrade_quality temp = {1300, 100, small, 150, none}, QGraphicsItem* parent = 0);
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
    QMediaPlayer * stone_sound;
    upgrade_quality stonetower;
};
#endif // STONETOWER_H
