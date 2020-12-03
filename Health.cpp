#include "Health.h"
#include <QFont>


Health::Health(QGraphicsItem * parent) : QGraphicsTextItem(parent)
{
    base_health = 20;
    setPlainText(QString("Base: ") + QString::number(base_health));
    setDefaultTextColor(Qt::darkCyan);
    setFont(QFont("Helvetica [Cronyx]", 16));
}

void Health::decrease(int amount)
{
    base_health -= amount;
    setPlainText(QString("Base: ") + QString::number(base_health));
}

int Health::getHealth() const
{
    return base_health;
}
