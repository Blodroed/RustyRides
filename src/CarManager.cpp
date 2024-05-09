//
// Created by Albert on 22.04.2024.
//

#include "../include/CarManager.h"
#include "../include/Car.h"
#include "../include/JsonParser.h"
#include <iostream>
#include <vector>

void CarManager::createCar(std::vector<Car> &cars, JsonParser &jsonParser) {
    /*
     * This function is used to create a car object and add it to the vector cars
     * The function takes a reference to the vector cars and a reference to the jsonParser
     * The function uses the standard cli input to get the car data
     * The function uses the jsonParser to export the car to the json document
     * The function then creates a car object and adds it to the vector cars
    */
    std::string regNr;
    std::string color;
    std::string model;
    std::string carType;
    int year;
    int price;
    int kmDriven;
    int seats;
    bool available;

    // this is just a standard cli input for the car
    // TODO: make the function work with inputs from other functions
    std::cout << "Add your first car!" << std::endl;
    std::cout << "========================" << std::endl;
    std::cout << "Registration number: " << std::endl;
    std::getline(std::cin, regNr);
    std::cout << "Color: " << std::endl;
    std::getline(std::cin, color);
    std::cout << "Model: " << std::endl;
    std::getline(std::cin, model);
    std::cout << "Car type: " << std::endl;
    std::getline(std::cin, carType);
    std::cout << "Year: " << std::endl;
    std::cin >> year; std::cin.ignore();
    std::cin >> year; std::cin.ignore();
    std::cout << "Price: " << std::endl;
    std::cin >> price; std::cin.ignore();
    std::cin >> price; std::cin.ignore();
    std::cout << "Km driven: " << std::endl;
    std::cin >> kmDriven; std::cin.ignore();
    std::cout << "Seats: " << std::endl;
    std::cin >> seats; std::cin.ignore();
    std::cout << "Available (1 or 0): " << std::endl;
    std::cin >> available; std::cin.ignore();

    Car car(regNr,color, model, carType, year, price, kmDriven, seats, available);

    // passing the car to the json document
    jsonParser.exportSingleCarToJson(car);

    // taking the reference of the vector cars and adding the car to it
    cars.push_back(car);
}

void CarManager::displayCar(const Car &car) {
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

void CarManager::displayAllCars(const std::vector<Car> &cars) {
    for (const auto &car : cars) {
        std::cout << "========================" << std::endl;
        std::cout << "RegNr: " << car.getRegNr() << std::endl;
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
}

void CarManager::addCarToVector(std::vector<Car> &cars, const Car &car) {
    cars.push_back(car); // damn program is so strong it can push cars
}

const Car* CarManager::searchForCarWithRegNR(const std::vector<Car> &cars, const std::string &regNr) {
    /*
     * This function is used to search for a car in the vector cars
     * The function takes a reference to the vector cars and a string regNr
     * The function iterates through the vector cars and compares the regNr
     * of each car with the provided regNr, if the regNr is found the function
     * returns a pointer to the car object, if the regNr is not found the function
     * returns a nullptr
     */
    for (auto &car : cars) {
        if (car.getRegNr() == regNr) {
            return &car;
        }
    }

    std::cout << "Car not found!" << std::endl;
    return nullptr;
}

void CarManager::editCarAllInstances(std::vector<Car> &cars, Car &car, JsonParser &jsonParser) {
    /*
     * In the function we take a reference to the vector cars and a reference to the car object
     * We then iterate through the vector cars and compare the regNr of each car with the regNr of the provided car
     * If the regNr is found we edit the car object in the vector cars
     * We then export the edited car to the json document
     */
    for (auto &carInVector : cars) {
        if (carInVector.getRegNr() == car.getRegNr()) {
            carInVector = car;
            jsonParser.editSingleCarToJson(car);
        }
    }
}

void CarManager::availabilitySwitch(Car& car) {
    if (car.getAvailable()) {
        car.setAvailable(false);
    } else {
        car.setAvailable(true);
    }
}

