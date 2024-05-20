//
// Created by Albert on 22.04.2024.
//

#ifndef HELLHUB_CARMANAGER_H
#define HELLHUB_CARMANAGER_H

#include "../include/Car.h"
#include "JsonParser.h"
#include <iostream>
#include <vector>

class CarManager {
public:
    static void createCar(std::vector<Car> &cars, const Car &newCar, JsonParser &jsonParser);
    static void displayCar(const Car &car);
    static void displayAllCars(const std::vector<Car> &cars);

    static void editCarObject(Car *car, Car &editedCar);
    static void editCarAllInstances(Car *car, Car &editedCar, JsonParser &jsonParser);

    static Car* searchForCarWithRegNr(std::vector<Car> &cars, const QString RegNr);
    static std::vector<const Car*> searchForCarWithSeveralParameters(const std::vector<Car> &cars, Car &searchCar);

    static void deleteCar(std::vector<Car> &cars, Car *car, JsonParser &jsonParser);

    static void availabilitySwitch(Car *car);
};


#endif //HELLHUB_CARMANAGER_H
