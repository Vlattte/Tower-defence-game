#ifndef STONEBULLET_H
#define STONEBULLET_H


#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

#include "Enemy.h"
#include "Stonetower.h"

class StoneBullet: public QObject, public QGraphicsPixmapItem
{
      Q_OBJECT
public:
    StoneBullet(bullet_types stone_type = small, QGraphicsItem* parent = 0);

    void play_death_sound(Enemy * enemy_ptr);

public slots:
    void move();

private:
    Enemy * enemy_ptr;
    int stone_damage;

    QMediaPlayer * enemy_death_sound;
    QMediaPlayer * victory;
};

#endif // STONEBULLET_H
