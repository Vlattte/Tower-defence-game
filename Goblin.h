#ifndef GOBLIN_H
#define GOBLIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QPointF>
#include <QLabel>
#include <QMediaPlayer>

#include "EnemyPoints.h"
#include "Enemy.h"

class Goblin: public QObject, public Enemy
{
            Q_OBJECT
public:
    Goblin(QGraphicsItem* parent = 0);
    ~Goblin();
//    void rotate(QPointF point);

//    int getHealth() const;

//    void chooseWay();

public slots:
   void move();
   void closing();

//protected:
//    QList<QPointF> list_of_points;
//    QPointF destination;

//    QMediaPlayer * goblin_pain;
//    QMediaPlayer * victory;
//    QMediaPlayer * lose;

//    QLabel * health_label = new QLabel();

//    int point_index;
//    int enemy_health;
//    int random_dest; //choose upper or bottom way on turn
//    int way_num;     //choose bottom or upper way

//    how_enemy_moves FP; //first package of points
};

#endif // GOBLIN_H
