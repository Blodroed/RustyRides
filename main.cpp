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
    // tests
    JsonParser jsonParser("../database/database-test.json");

    // testForStuff::removeCarTest(jsonParser);
    // testForStuff::editCarTest(jsonParser);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}