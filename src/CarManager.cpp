//
// Created by Alber on 22.04.2024.
//

#include "../include/CarManager.h"
#include "../include/Car.h"
#include <iostream>

Car CarManager::createCar() {
    std::string color;
    std::string model;
    std::string carType;
    int year;
    int price;
    int kmDriven;

    std::cout << "Add your first car!" << std::endl;
    std::cout << "Color: " << std::endl;
    std::getline(std::cin, color);
    std::cout << "Model: " << std::endl;
    std::getline(std::cin, model);
    std::cout << "Car type: " << std::endl;
    std::getline(std::cin, carType);
    std::cout << "Year: " << std::endl;
    std::cin >> year;
    std::cin.ignore();
    std::cout << "Price: " << std::endl;
    std::cin >> price;
    std::cin.ignore();
    std::cout << "Km driven: " << std::endl;
    std::cin >> kmDriven;
    Car car(color, model, carType, year, price, kmDriven);

    return car;
}

void CarManager::displayCar(const Car& car) {
    std::cout << "========================" << std::endl;
    std::cout << "Car added!" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "Color: " << car.getColor() << std::endl;
    std::cout << "Model: " << car.getModel() << std::endl;
    std::cout << "Car type: " << car.getCarType() << std::endl;
    std::cout << "Year: " << car.getYear() << std::endl;
    std::cout << "Price: " << car.getPrice() << std::endl;
    std::cout << "Km driven: " << car.getKmDriven() << std::endl;
    if (car.getAvailable()) {
        std::cout << "Available: Yes" << std::endl;
    } else {
        std::cout << "Available: No" << std::endl;
    }
}