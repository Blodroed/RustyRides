#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"
#include "include/Customer.h"
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

    // init customer manager
    CustomerManager customerManager(customers);

    std::cout << "C++ version: " << __cplusplus << std::endl;
    // init json parser with database path
    JsonParser jsonParser("../database/database-test.json");
    jsonParser.importCarsFromJson(cars);
    CarManager::displayAllCars(cars);

    QApplication a(argc, argv);
    MainWindow w(jsonParser, customers);
    w.show();
    return a.exec();
}
