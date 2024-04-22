//
// Created by Albert on 17.04.2024.
//

#include <iostream>
#include "include/Car.h"
#include "include/CarManager.h"

int main() {
    CarManager carManager;
    Car car = carManager.createCar();
    carManager.displayCar(car);
    return 0;
}