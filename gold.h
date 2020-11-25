#ifndef GOLD_H
#define GOLD_H

#include <QGraphicsTextItem>

class Gold : public QGraphicsTextItem
{
public:
    Gold(QGraphicsItem * parent = 0);
    void decrease(int amount);
    void increase(int amount);
    int getGold() const;
private:
    int player_gold;
};

#endif // GOLD_H
