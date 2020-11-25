#include "Chat.h"

#include <QFont>

Chat::Chat(QGraphicsItem *parent)
{
    first_string  = QString ("Good");
    second_string = QString ("Luck");
    third_string  = QString ("Have");
    fourth_string = QString ("Fun");

    setPlainText(first_string + QString ("\n") + second_string + QString ("\n") + third_string + QString ("\n") + fourth_string);
    setDefaultTextColor(Qt::cyan);
    setFont(QFont("Helvetica [Cronyx]", 8));
}

void Chat::addText(QString string)
{
    fourth_string = third_string;
    third_string  = second_string;
    second_string = first_string;
    first_string  = string;

    setPlainText(first_string + QString ("\n") + second_string + QString ("\n") + third_string + QString ("\n") + fourth_string);
}
