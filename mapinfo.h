#ifndef MAPINFO_H
#define MAPINFO_H

#include <QPointF>
#include <QString>

#include "EnemyPoints.h"

//info about any map: points of enemy path, tower points, pictures of map
struct map_varieties
{
    QPointF base_point;         //place of the base
    QString map_name;           //name of background image
    QPointF tbp[10];            //tower builder points
    how_enemy_moves bottom_way; //upper enemy way
    how_enemy_moves upper_way;  //bottom enemy way

};

enum number_of_map
{
    first_map,
    second_map
};


class map_settings
{
public:
    map_settings();
    void set_varieties(number_of_map n);    //set varieties
    map_varieties variety;                  //struct with all varieties of map
};

#endif // MAPINFO_H
