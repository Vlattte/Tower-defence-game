#include <QApplication>
#include "mainwindow.h"

MainWindow * window;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window = new MainWindow();
    window->show();

    return a.exec();
}
