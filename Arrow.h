#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

#include "Goblin.h"
#include "ArrowTower.h"

class Arrow: public QObject, public QGraphicsPixmapItem
{
      Q_OBJECT
public:
    Arrow(bullet_types arrow_type = small, QGraphicsItem* parent = 0);

public slots:
    void move();

private:
    Enemy * enemy_ptr;
    int arrow_damage;

    QMediaPlayer * goblin_dead;
    QMediaPlayer * victory;
};

#endif // ARROW_H
