#include "Base.h"

#include <QTimer>

Base::Base(QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    //set the picture of the base
    setPixmap(QPixmap(":/images/images/base.png"));

//    //set current time label
//    cur_time = new QLabel();
//    cur_timer = new QTimer();


//    connect(cur_timer, SIGNAL(timeout()), this, SLOT(time_update()));

//    cur_timer->start(1000);
}

//void Base::time_update()
//{
//    cur_time->setText(QTime::currentTime().toString("hh:mm:ss"));
//}

