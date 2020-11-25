#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsItem>
#include <QObject>

#include "Upgrades.h"

class MainTower: public QGraphicsPixmapItem
{
public:
    MainTower();
    virtual double distanseBetweenItems(QGraphicsItem *item);

    upgrade_quality tower_upgrade;
};

#endif // TOWER_H
