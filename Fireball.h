#ifndef FIREBALL_H
#define FIREBALL_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

#include "Enemy.h"
#include "Fireballtower.h"

class FireBall: public QObject, public QGraphicsPixmapItem
{
      Q_OBJECT
public:
    FireBall(bullet_types type = small, QGraphicsItem* parent = 0);

public slots:
    void move();

private:
    Enemy * enemy_ptr = new Enemy();
    int fire_damage;

    QMediaPlayer * goblin_dead;
    QMediaPlayer * victory;
};


#endif // FIREBALL_H
