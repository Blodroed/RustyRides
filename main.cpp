#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"
#include "include/CustomerManager.h"
#include "include/JsonParser.h"
// tests
#include "test/testForStuff.h"

#include <vector>
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    // init vectors
    std::vector<Car> cars;
    std::vector<Customer> customers;

    std::cout << "C++ version: " << __cplusplus << std::endl;
    // init json parser with database path
    JsonParser jsonParser("../database/database-test.json");

    QApplication a(argc, argv);
    MainWindow w(jsonParser);
    w.show();
    return a.exec();
}
