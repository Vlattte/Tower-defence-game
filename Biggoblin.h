#ifndef BIGGOBLIN_H
#define BIGGOBLIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QPointF>
#include <QLabel>
#include <QMediaPlayer>

#include "EnemyPoints.h"
#include "Enemy.h"

class BigGoblin: public QObject, public Enemy
{
       Q_OBJECT
public:
    BigGoblin(QGraphicsItem* parent = 0);
    ~BigGoblin();
//    void rotate(QPointF point);

//    void decreaseHealth(int damage);
//    int getHealth() const;

//    void chooseWay();

public slots:
   void move();
   void closing();

//private:
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

#endif // BIGGOBLIN_H
