#include "Towerupgrade.h"
#include "ui_towerupgrade.h"
#include "game.h"
#include "UpdateHelper.h"

#include <QGraphicsItem>
#include <QLineF>

extern Game * game;

TowerUpgrade::TowerUpgrade(upgrade_quality &tower_stats, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TowerUpgrade)
{
    temp_stats = &tower_stats;

    //check what stats was already upgraded
    speed_flag = temp_stats->is_upgraded.shooting_speed;
    size_flag = temp_stats->is_upgraded.bullet_size;
    range_flag = temp_stats->is_upgraded.shooting_range;

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //set sounds
    not_enough_gold = new QMediaPlayer();
    not_enough_gold->setMedia(QUrl("qrc:/sounds/sounds/not_enough_gold_fUp.wav"));
}

TowerUpgrade::~TowerUpgrade()
{
    delete ui;
}

void TowerUpgrade::on_pushButton_clicked()
{
    if (speed_flag == false)
    {
        if (game->gold->getGold() >= 300)
        {
            //change shooting speed
            temp_stats->is_upgraded.shooting_speed = true;
            temp_stats->shooting_speed /= 2;
            temp_stats->num = update_num::speed;

            //get money for upgrade
            game->gold->decrease(300);

            game->chat->addText(QString("Shooting speed was increased"));

            UpdateHelper * helper = new UpdateHelper(*temp_stats);
            int hammerX = pos().x() - 200;
            int hammerY = pos().y() - 120;

            helper->setPos(hammerX, hammerY);
            game->scene->addItem(helper);
        }
        else
        {
            game->chat->addText(QString("You need "
            + QString::number(300 - game->gold->getGold()) + " gold for upgrade."));

            //sound of lake of gold for upgrade
            if (not_enough_gold->state() == QMediaPlayer::PlayingState)
            {
                not_enough_gold->setPosition(0);
            }
            else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
            {
                not_enough_gold->play();
            }
        }
    }
    else
    {
        game->chat->addText(QString("We can't upgrade shooting speed more"));
    }


    close();
}

void TowerUpgrade::on_pushButton_2_clicked()
{
    //change type of bullet to bigger one
    if (size_flag == false)
    {
        if (game->gold->getGold() >= 300)
        {
            game->chat->addText(QString("Type of bullet was changed"));
            temp_stats->bullet_size = large;
            temp_stats->is_upgraded.bullet_size = true;

            //get money for upgrade
            game->gold->decrease(300);

            UpdateHelper * helper = new UpdateHelper(*temp_stats);
            int hammerX = pos().x() - 200;
            int hammerY = pos().y() - 120;

            helper->setPos(hammerX, hammerY);
            game->scene->addItem(helper);
        }
        else
        {
            game->chat->addText(QString("You need "
            + QString::number(300 - game->gold->getGold()) + " gold for upgrade."));

            //sound of lake of gold for upgrade
            if (not_enough_gold->state() == QMediaPlayer::PlayingState)
            {
                not_enough_gold->setPosition(0);
            }
            else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
            {
                not_enough_gold->play();
            }
        }
    }
    else
    {
        game->chat->addText(QString("We can't upgrade bullet size more"));
    }

    close();
}

void TowerUpgrade::on_pushButton_3_clicked()
{
    //change type of bullet to bigger one
    if (range_flag == false)
    {
        if (game->gold->getGold() >= 300)
        {
            game->chat->addText(QString("Number of bullets was increased"));
            temp_stats->shooting_range *= 1.5;
            temp_stats->is_upgraded.shooting_range = true;

            //get money for upgrade
            game->gold->decrease(300);

            UpdateHelper * helper = new UpdateHelper(*temp_stats);
            int hammerX = pos().x() - 200;
            int hammerY = pos().y() - 120;

            helper->setPos(hammerX, hammerY);
            game->scene->addItem(helper);
        }
        else
        {
            game->chat->addText(QString("You need "
            + QString::number(300 - game->gold->getGold()) + " gold for upgrade."));

            //sound of lake of gold for upgrade
            if (not_enough_gold->state() == QMediaPlayer::PlayingState)
            {
                not_enough_gold->setPosition(0);
            }
            else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
            {
                not_enough_gold->play();
            }
        }
    }
    else
    {
        game->chat->addText(QString("We can't upgrade bullet number more"));
    }
    close();
}

void TowerUpgrade::on_pushButton_4_clicked()
{
    //cancel
    close();
}
