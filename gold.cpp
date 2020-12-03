#include "gold.h"

#include <QFont>
#include <QLabel>

Gold::Gold(QGraphicsItem * parent)
{
    player_gold = 1200;
    setPlainText(QString("Gold: ") + QString::number(player_gold));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("Helvetica [Cronyx]", 16));
}


void Gold::decrease(int amount)
{
    player_gold -= amount;
    setPlainText(QString("Gold: ") + QString::number(player_gold));
}

void Gold::increase(int amount)
{
    player_gold += amount;
    setPlainText(QString("Gold: ") + QString::number(player_gold));
}

int Gold::getGold() const
{
    return player_gold;
}
