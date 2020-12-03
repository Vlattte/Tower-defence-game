#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

#include "Enemy.h"
#include "Upgrades.h"
#include "ArrowTower.h"

class Arrow: public QObject, public QGraphicsPixmapItem
{
      Q_OBJECT
public:
    Arrow(bullet_types arrow_type = small, QGraphicsItem* parent = 0);

    void play_death_sound(Enemy * enemy_ptr);

public slots:
    void move();

private:
    Enemy * enemy_ptr;
    int arrow_damage;

    QMediaPlayer * enemy_death_sound;
    QMediaPlayer * victory;
};

#endif // ARROW_H
