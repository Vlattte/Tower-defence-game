#ifndef TOWERBUILDER_H
#define TOWERBUILDER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QMediaPlayer>
#include <QObject>

class TowerBuilder: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TowerBuilder(QGraphicsItem * parent = 0);

    void mousePressEvent (QGraphicsSceneMouseEvent * event);

public slots:
    void turnGameON();
private:
    QMediaPlayer * not_enough_gold;
    QMediaPlayer * anger;
    int until_anger;
};

#endif // TOWERBUILDER_H
