#include "Tower.h"

MainTower::MainTower()
{
    //it's helpless
    tower_upgrade.bullet_size = small;
    tower_upgrade.shooting_range = 80;
    tower_upgrade.shooting_speed = 1100;
}



double MainTower::distanseBetweenItems(QGraphicsItem *item)
{
    return 47;
}
