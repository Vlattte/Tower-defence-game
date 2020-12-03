#ifndef BONE_H
#define BONE_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

#include "Skeleton.h"
#include "Enemy.h"

class Bone: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bone(QGraphicsItem* parent = 0);

    QMediaPlayer * lose;
public slots:
    void move();
};

#endif // BONE_H
