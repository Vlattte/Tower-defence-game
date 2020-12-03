#ifndef SKELETON_H
#define SKELETON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QPointF>
#include <QLabel>
#include <QMediaPlayer>

#include "EnemyPoints.h"
#include "Enemy.h"

class Skeleton: public QObject, public Enemy
{
    Q_OBJECT
public:
    Skeleton(QGraphicsItem * parent = 0);
    ~Skeleton();

    void shoot();

    QMediaPlayer * bone_sound;

public slots:
   void aquire();
   void move();
   void closing();
};

#endif // SKELETON_H
