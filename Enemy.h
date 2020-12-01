#ifndef ENEMY_H
#define ENEMY_H

#include <QPointF>
#include <QList>
#include <QMediaPlayer>
#include <QLabel>
#include <QGraphicsItem>

#include "EnemyPoints.h"

class Enemy: public QGraphicsPixmapItem
{
public:
    Enemy();

    void decreaseHealth(int damage);
    int getHealth() const;

    void chooseWay();
    void rotate(QPointF point);

    int gold_for_kill;

protected:
    QList<QPointF> list_of_points;
    QPointF destination;

    QMediaPlayer * goblin_pain;
    QMediaPlayer * victory;
    QMediaPlayer * lose;

    QLabel * health_label = new QLabel();

    int point_index;
    int enemy_health;
    int random_dest; //choose upper or bottom way on turn
    int way_num;     //choose bottom or upper way

    how_enemy_moves FP; //first package of points
};

#endif // ENEMY_H
