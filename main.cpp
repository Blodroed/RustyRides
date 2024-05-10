#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"
#include "include/CustomerManager.h"
#include "include/JsonParser.h"

// tests, remove when done TODO
#include "test/carAddToJsonTest.h"

#include <vector>
#include <iostream>

#include <QApplication>
#include <vector>
#include <iostream>

int main(int argc, char *argv[])
{
    // init vectors
    std::vector<Car> cars;
    std::vector<Customer> customers;

    std::cout << "C++ version: " << __cplusplus << std::endl;
    
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
