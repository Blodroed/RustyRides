//
// Created by Alber on 22.04.2024.
//

#ifndef HELLHUB_CARMANAGER_H
#define HELLHUB_CARMANAGER_H

#include "Car.h"
#include "JsonParser.h"
#include <iostream>
#include <vector>

class CarManager {
public:
    static void createCar(std::vector<Car> &cars, JsonParser &jsonParser);
    void displayCar(const Car &car);
    static void displayAllCars(const std::vector<Car> &cars);
    static void addCarToVector(std::vector<Car> &cars, const Car &car);
    static void editCarAllInstances(std::vector<Car> &cars, Car& car, JsonParser &jsonParser);
    static const Car* searchForCarWithRegNR(const std::vector<Car> &cars, const std::string &regNr);
    static Car* searchForCarWithSeveralParameters(const std::vector<Car> &cars); // TODO

    void availabilitySwitch(Car &car);
};


#endif //HELLHUB_CARMANAGER_H
