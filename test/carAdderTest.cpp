//
// Created by Albert on 22.04.2024.
//

#include "../include/Car.h"
#include "../include/CarManager.h"

#include <vector>

int main() {
    CarManager carManager;
    std::vector<Car> cars;

    Car car = carManager.createCar(cars);

    carManager.displayCar(car);
    return 0;
}