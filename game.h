#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QObject>
#include <QLabel>

#include "Tower.h"
#include "Health.h"
#include "gold.h"
#include "Chat.h"

//important structures
#include "mapinfo.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(number_of_map map_num);
    void changeCursor(QString filename);
    void mouseMoveEvent (QMouseEvent * event);
    void keyPressEvent (QKeyEvent* event);

    QGraphicsScene * scene;
    QGraphicsPixmapItem * cursor;
    MainTower * build;

    Health * base_health = new Health();
    Gold * gold = new Gold();
    Chat * chat = new Chat();

    int pause = 1;

    //spawn numbers
    int spawn_number[4];
    int index;
    bool wave_change_ability;

    bool was_i_already_angry;

    number_of_map mn;         //map number for other classes
    map_settings settings;  //all map varieties
public slots:
    void spawn_simple_enemy();

};

#endif // GAME_H
