//
// Created by Albert on 22.04.2024.
//

#include "../include/Car.h"
#include "../include/CarManager.h"

#include <vector>

int carAdderTest() {
    CarManager carManager;
    std::vector<Car> cars;

    carManager.createCar(cars);
    return 0;
}