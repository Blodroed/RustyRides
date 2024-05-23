#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"
#include "include/Customer.h"
#include "include/CustomerManager.h"
#include "include/Lease.h"
#include "include/LeaseManager.h"
#include "include/JsonParser.h"
// tests

#include <vector>
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    // init vectors
    std::vector<Car> cars;
    std::vector<Customer> customers;
    std::vector<Lease> leases;

    // init customer manager

    std::cout << "C++ version: " << __cplusplus << std::endl;
    // init json parser with database path
    JsonParser jsonParser("../database/database-test.json");
    jsonParser.importCarsFromJson(cars);
    jsonParser.importCustomersFromJson(customers);
    jsonParser.importLeasesFromJson(leases);

    QApplication a(argc, argv);
    MainWindow w(jsonParser, customers, cars, leases);
    w.show();
    return a.exec();
}
