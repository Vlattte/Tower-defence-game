#include "Info.h"
#include "ui_info.h"
#include "game.h"

#include <QDebug>

extern Game * game;

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
}

Info::~Info()
{
    game->pause = 1;
    delete ui;
}

