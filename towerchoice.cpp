#include "towerchoice.h"
#include "ui_towerchoice.h"

#include <QLineF>

#include "Fireballtower.h"
#include "ArrowTower.h"
#include "Stonetower.h"
#include "game.h"


extern Game * game;

TowerChoice::TowerChoice(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TowerChoice)
{

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);

    //set sounds
    not_enough_gold = new QMediaPlayer();
    not_enough_gold->setMedia(QUrl("qrc:/sounds/sounds/Not_enough_gold.wav"));
}

TowerChoice::~TowerChoice()
{
    delete ui;
}


void TowerChoice::on_pushButton_clicked()
{
    if (game->gold->getGold() >= 200)
    {
           game->build = new ArrowTower();
           game->gold->decrease(200);
           game->chat->addText("Simple tower was built, my Lord");
    }
    else
    {
        game->chat->addText("Not enough gold for simple tower, my Lord!");

        //sound of lake of gold
        if (not_enough_gold->state() == QMediaPlayer::PlayingState)
        {
            not_enough_gold->setPosition(0);
        }
        else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
        {
            not_enough_gold->play();
        }
    }


    close();
}

void TowerChoice::on_pushButton_2_clicked()
{
    if (game->gold->getGold() >= 400)
    {
           game->build = new FireBallTower();
           game->gold->decrease(400);
           game->chat->addText("Fireball tower was built, my Lord");
    }
    else
    {
        game->chat->addText("Not enough gold for simple tower, my Lord!");

        //sound of lake of gold
        if (not_enough_gold->state() == QMediaPlayer::PlayingState)
        {
            not_enough_gold->setPosition(0);
        }
        else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
        {
            not_enough_gold->play();
        }
    }


    close();
}

void TowerChoice::on_pushButton_3_clicked()
{
    if (game->gold->getGold() >= 300)
    {
           game->build = new StoneTower();
           game->gold->decrease(300);
           game->chat->addText("Stonetower tower was built, my Lord");
    }
    else
    {
        game->chat->addText("Not enough gold for simple tower, my Lord!");

        //sound of lake of gold
        if (not_enough_gold->state() == QMediaPlayer::PlayingState)
        {
            not_enough_gold->setPosition(0);
        }
        else if (not_enough_gold->state() == QMediaPlayer::StoppedState)
        {
            not_enough_gold->play();
        }
    }


    close();
}

void TowerChoice::on_pushButton_4_clicked()
{
    this->close();
}
