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
    if (speed_flag == true)
    {
        if (game->gold->getGold() >= 300)
        {
            //change shooting speed
            temp_stats->shooting_speed /= 2;

            game->chat->addText(QString("Shooting speed was increased"));

            QImage image (":/images/images/archer.png");
            QGraphicsPixmapItem * archer = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            game->scene->addItem(archer);

            int archerX = pos().x() - 200;
            int archerY = pos().y() - 140;


            archer->setPos(archerX, archerY);


            UpdateHelper * helper = new UpdateHelper(*temp_stats);
            int hammerX = pos().x() - 200;
            int hammerY = pos().y() - 120;

            helper->setPos(hammerX, hammerY);
            game->scene->addItem(helper);

            speed_flag = false;
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
    if (size_flag == true)
    {
        if (game->gold->getGold() >= 300)
        {
            game->chat->addText(QString("Type of bullet was changed"));
            temp_stats->bullet_size = large;

            UpdateHelper * helper = new UpdateHelper(*temp_stats);
            int hammerX = pos().x() - 200;
            int hammerY = pos().y() - 120;

            helper->setPos(hammerX, hammerY);
            game->scene->addItem(helper);



            size_flag = false;
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
    if (shooting_range == true)
    {
        if (game->gold->getGold() >= 300)
        {
            game->chat->addText(QString("Number of bullets was increased"));
            temp_stats->shooting_range *= 1.5;

            UpdateHelper * helper = new UpdateHelper(*temp_stats);
            int hammerX = pos().x() - 200;
            int hammerY = pos().y() - 120;

            helper->setPos(hammerX, hammerY);
            game->scene->addItem(helper);

            shooting_range = false;
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
