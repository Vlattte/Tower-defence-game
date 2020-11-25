#ifndef TOWERUPGRADE_H
#define TOWERUPGRADE_H

#include <QDialog>
#include <QMediaPlayer>

#include <Upgrades.h>

namespace Ui {
class TowerUpgrade;
}

class TowerUpgrade : public QDialog
{
    Q_OBJECT

public:
    explicit TowerUpgrade(upgrade_quality &tower_stats ,QWidget *parent = nullptr);
    ~TowerUpgrade();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TowerUpgrade *ui;
    QMediaPlayer * not_enough_gold;

    upgrade_quality *temp_stats;
    bool size_flag = true;
    bool speed_flag = true;
    bool shooting_range = true;
};

#endif // TOWERUPGRADE_H
