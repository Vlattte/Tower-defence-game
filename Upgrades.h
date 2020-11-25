#ifndef UPGRADES_H
#define UPGRADES_H

enum bullet_types
{
    small,
    large
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
    update_num num;

};


#endif // UPGRADES_H
