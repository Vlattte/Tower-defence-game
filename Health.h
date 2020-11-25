#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

class Health : public QGraphicsTextItem
{
public:
    Health(QGraphicsItem * parent = 0);
    void decrease(int amount);
    int getHealth() const;
private:
    int base_health;
};

#endif // HEALTH_H
