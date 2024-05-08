//
// Created by Albert on 22.04.2024.
//

#include "../include/Car.h"
#include "../include/CarManager.h"
#include "../include/JsonParser.h"

#include <vector>

int carAdderTest() {
    CarManager carManager;
    std::vector<Car> cars;
    JsonParser jsonParser("../database/database-test.json");

    carManager.createCar(cars, jsonParser);
    return 0;
}