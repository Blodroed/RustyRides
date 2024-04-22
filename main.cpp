//
// Created by Albert on 17.04.2024.
//

#include <vector>
#include "include/Car.h"
#include "include/CarManager.h"

int main() {
    CarManager carManager;
    std::vector<Car> cars;

    Car car = carManager.createCar();
    carManager.addCarToVector(cars, car);

    carManager.displayCar(car);
    return 0;
}