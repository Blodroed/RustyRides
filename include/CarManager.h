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
    Car createCar();
    void displayCar(const Car& car);
    void addCarToVector(std::vector<Car> &cars, const Car &car);

    void availabilitySwitch(Car& car);
};


#endif //HELLHUB_CARMANAGER_H
