#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"
#include "include/JsonParser.h"

// tests, remove when done TODO
#include "test/carAddToJsonTest.h"

#include <vector>
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "C++ version: " << __cplusplus << std::endl;
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
