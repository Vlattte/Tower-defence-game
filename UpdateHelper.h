#ifndef UPDATEHELPER_H
#define UPDATEHELPER_H

#include <QGraphicsItem>

#include "Upgrades.h"

class UpdateHelper: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    UpdateHelper(upgrade_quality tower_stats, QGraphicsItem* parent = 0);

    upgrade_quality temp;
public slots:
    void rebuilder();
};

#endif // UPDATEHELPER_H