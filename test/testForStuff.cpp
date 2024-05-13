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
    std::vector<Car> cars;
    JsonParser jsonParser("../database/database-test.json");

    CarManager::createCar(cars, jsonParser);
}

void testForStuff::editCarTest(JsonParser &jsonParser) {
    // initialize the cars data from the json file
    std::vector<Car> cars;
    jsonParser.importCarsFromJson(cars);

    Car *car = CarManager::searchForCarWithRegNR(cars, "AB12345");
    if (car == nullptr) {
        std::cout << "Car not found" << std::endl;
        return;
    }
    CarManager::displayCar(*car);  // dereferenced before passing to the function

    // make new car Obect for editing
    Car editedCar("AB12345", "Black", "Volvo", "Diesel", 2020, 1000, 10000, 5, true);

    CarManager::editCarAllInstances(car, editedCar, jsonParser);
    CarManager::displayCar(*car);  // dereferenced before passing to the function
    CarManager::displayAllCars(cars);
}

void testForStuff::removeCarTest(JsonParser &jsonParser) {
    std::vector<Car> cars;
    jsonParser.importCarsFromJson(cars);

    Car *car = CarManager::searchForCarWithRegNR(cars, "AB12345");

    CarManager::displayAllCars(cars);
    CarManager::displayCar(*car);  // dereferenced before passing to the function

    CarManager::deleteCar(cars, car, jsonParser);
    CarManager::displayAllCars(cars);
}