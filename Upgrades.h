#ifndef UPGRADES_H
#define UPGRADES_H

#include <QString>

enum bullet_types
{
    small,
    large
};

struct upgrade_status
{
   bool shooting_speed = false;
   bool bullet_size = false;
   bool shooting_range = false;
};

enum update_num
{
    none,
    speed,
    range,
    size
};


struct upgrade_quality
{
    int shooting_speed;
    int shooting_range;
    bullet_types bullet_size;
    int tower_price;
    update_num num;
    upgrade_status is_upgraded;
};


#endif // UPGRADES_H
