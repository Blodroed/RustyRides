//
// Created by Alber on 09.05.2024.
//

#include "testForStuff.h"
#include "../include/CarManager.h"
#include "../include/JsonParser.h"

#include <vector>

void testForStuff::carAddToJsonTest() {
    std::string filepath;
    JsonParser jsonParser("../database/database-test.json");
    std::vector<Car> cars;

    jsonParser.importCarsFromJson(cars);
    CarManager::displayAllCars(cars);
    CarManager::createCar(cars, jsonParser);
    CarManager::displayAllCars(cars);
}

void testForStuff::carAdderTest() {
    CarManager carManager;
    std::vector<Car> cars;
    JsonParser jsonParser("../database/database-test.json");

    carManager.createCar(cars, jsonParser);
}