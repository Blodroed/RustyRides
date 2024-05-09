#include "include/mainwindow.h"
#include "include/Car.h"
#include "include/CarManager.h"
#include "include/JsonParser.h"
#include "test/testForStuff.h"

// tests remove when done

#include <vector>
#include <iostream>

#include <QApplication>

int main(int argc, char *argv[])
{
    std::cout << "C++ version: " << __cplusplus << std::endl;
    // tests
    JsonParser jsonParser("../database/database-test.json");

    testForStuff::editCarTest(jsonParser);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
