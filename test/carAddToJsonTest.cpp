//
// Created by Albert on 26.04.2024.
//

#include "../include/JsonParser.h"
#include "../include/Car.h"
#include "../include/CarManager.h"

#include <vector>

int carAddToJsonTest() {
    std::string filepath;
    JsonParser jsonParser("../database/database-test.json");
    std::vector<Car> cars;

    jsonParser.importCarFromJson(cars);
    CarManager::displayAllCars(cars);
    CarManager::createCar(cars, jsonParser);
    CarManager::displayAllCars(cars);
    return 0;
}