#ifndef TOWERCHOICE_H
#define TOWERCHOICE_H

#include <QDialog>
#include <QMediaPlayer>

namespace Ui {
class TowerChoice;
}

class TowerChoice : public QDialog
{
    Q_OBJECT

public:
    explicit TowerChoice(QWidget *parent = nullptr);
    ~TowerChoice();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::TowerChoice *ui;
    QMediaPlayer * not_enough_gold;
};

#endif // TOWERCHOICE_H
