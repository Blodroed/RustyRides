//
// Created by Alber on 22.04.2024.
//

#ifndef HELLHUB_CARMANAGER_H
#define HELLHUB_CARMANAGER_H

#include "Car.h"
#include <iostream>
#include <vector>

class CarManager {
public:
    void createCar(std::vector<Car> &cars);
    void displayCar(const Car& car);
    static void displayAllCars(const std::vector<Car> &cars);
    static void addCarToVector(std::vector<Car> &cars, const Car &car);

    void availabilitySwitch(Car& car);
};


#endif //HELLHUB_CARMANAGER_H
