#include "Enemy.h"

Enemy::Enemy()
{

}


void Enemy::decreaseHealth(int damage)
{
    enemy_health -= damage;
    health_label->setText(QString::number(enemy_health));

    //sound of goblins death
    if (goblin_pain->state() == QMediaPlayer::PlayingState)
    {
        goblin_pain->setPosition(0);
    }
    else if (goblin_pain->state() == QMediaPlayer::StoppedState)
    {
        goblin_pain->play();
    }
}

int Enemy::getHealth() const
{
    return enemy_health;
}

void Enemy::chooseWay()
{
    //================random=enemy=move=======================
    int lowest = 1, highest = 2;
    int range = (highest-lowest) + 1;
    random_dest = int(rand() % 2) + 1;
    way_num = int(rand() % 2) + 1;

//    random_dest = lowest + int(range * (rand() / (RAND_MAX + 1.0)));
//    way_num = lowest + int(range * (rand() / (RAND_MAX + 1.0)));
    //========================================================
}

void Enemy::rotate(QPointF point)
{
    QLineF line(pos(),point);
    setRotation(-1 * line.angle());
}
