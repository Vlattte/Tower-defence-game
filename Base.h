#ifndef BASE_H
#define BASE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QLabel>


class Base: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Base(QGraphicsItem* parent = 0);

//public slots:
//     void time_update();

//private:
//    QLabel * cur_time;
//    QTimer * cur_timer;
};

#endif // BASE_H
