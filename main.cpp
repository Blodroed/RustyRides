#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"

#include <QApplication>
#include <vector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
