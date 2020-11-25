#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "game.h"

Game * game;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set window size
    this->resize(600, 447);

    //set background
    QPalette Pal(palette());
        QImage background2(":/images/images/preview.png");
        Pal.setBrush(QPalette::Background, background2);
        this->setAutoFillBackground(true);
        this->setPalette(Pal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    setToolButtonStyle(Qt::ToolButtonStyle::ToolButtonTextUnderIcon);
    this->close();
    game = new Game();
    game->show();
}
