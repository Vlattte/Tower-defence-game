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

public slots:
    void move();

private:
    Enemy * enemy_ptr = new Enemy();
    int stone_damage;

    QMediaPlayer * goblin_dead;
    QMediaPlayer * victory;
};

#endif // STONEBULLET_H
