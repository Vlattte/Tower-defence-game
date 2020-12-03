#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "mapinfo.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_quit_button_clicked();

    void on_grass_button_clicked();

    void on_sand_button_clicked();

private:
    Ui::MainWindow *ui;
    number_of_map number;
};

#endif // MAINWINDOW_H
