//
// Created by Alber on 22.04.2024.
//

#ifndef HELLHUB_CARMANAGER_H
#define HELLHUB_CARMANAGER_H

#include "Car.h"
#include <iostream>

class CarManager {
public:
    Car createCar();
    void displayCar(const Car& car);
};


#endif //HELLHUB_CARMANAGER_H
