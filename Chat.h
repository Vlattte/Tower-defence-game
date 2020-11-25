#ifndef CHAT_H
#define CHAT_H

#include <QGraphicsTextItem>

class Chat :public QGraphicsTextItem
{
public:
    Chat(QGraphicsItem * parent = nullptr);
    void addText(QString string);

    QString first_string;
    QString second_string;
    QString third_string;
    QString fourth_string;
};

#endif // CHAT_H
