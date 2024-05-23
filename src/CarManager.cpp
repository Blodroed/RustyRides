#include "../include/CarManager.h"
#include "../include/Car.h"
#include "../include/JsonParser.h"
#include <iostream>
#include <vector>
#include <QDebug>

// === CarManager functions ===
void CarManager::createCar(std::vector<Car> &cars, const Car &newCar, JsonParser &jsonParser) {
    jsonParser.exportSingleCarToJson(newCar);
    cars.push_back(newCar);
}

// searching for a car object with the registration number
Car* CarManager::searchForCarWithRegNr(std::vector<Car> &cars, const QString RegNr) {
    for (auto &car : cars) {
        if (car.getRegNr() == RegNr) {
            return &car;
        }
    }
    qDebug() << "Car not found with: " << RegNr;
    return nullptr;
}

// editing a car object
void CarManager::editCarObject(Car *car, Car &editedCar) {
    if (car == nullptr) {
        std::cout << "Car pointer is not pointing to anything" << std::endl;
        return;
    }

    if (car->getRegNr() == editedCar.getRegNr()) {
        *car = editedCar; // Directly assign the edited car since RegNr matches
    } else {
        std::cout << "The regNr of the car object and the edited car object do not match" << std::endl;
    }
}

// editing a car object from the vector and updating the json file
void CarManager::editCarAllInstances(Car *car, Car &editedCar, JsonParser &jsonParser) {
    editCarObject(car, editedCar);
    jsonParser.editSingleCarToJson(editedCar);
}

// deleting a car object from the vector and updating the json file
void CarManager::deleteCar(std::vector<Car> &cars, Car *car, JsonParser &jsonParser) {
    if (car == nullptr) {
        std::cout << "Car not found" << std::endl;
        return;
    }

    if (!car->getAvailable()) {
        std::cout << "Car is currently rented and cannot be deleted." << std::endl;
        return;
    }

    jsonParser.deleteSingleCarFromJson(*car);

    for (auto it = cars.begin(); it != cars.end(); ++it) {
        if (&(*it) == car) {
            cars.erase(it);
            std::cout << "Car deleted" << std::endl;
            return;
        }
    }
}

std::vector<const Car*> CarManager::searchForCarWithSeveralParameters(const std::vector<Car> &cars,
                                                                      Car &searchCar) {
    std::vector<const Car*> foundCars;

    for (const auto &car : cars) {
        if ((searchCar.getRegNr().isEmpty() || car.getRegNr() == searchCar.getRegNr()) &&
            (searchCar.getColor().isEmpty() || car.getColor() == searchCar.getColor()) &&
            (searchCar.getModel().isEmpty() || car.getModel() == searchCar.getModel()) &&
            (searchCar.getCarType().isEmpty() || car.getCarType() == searchCar.getCarType()) &&
            (searchCar.getFuelType().isEmpty() || car.getFuelType() == searchCar.getFuelType()) &&
            (searchCar.getYear() == 0 || car.getYear() == searchCar.getYear()) &&
            (searchCar.getPrice() == 0 || car.getPrice() == searchCar.getPrice()) &&
            (searchCar.getKmDriven() == 0 || car.getKmDriven() == searchCar.getKmDriven()) &&
            (searchCar.getSeats() == 0 || car.getSeats() == searchCar.getSeats())) {
            foundCars.push_back(&car);
        }
    }
    return foundCars;
}

// === CLI related functions ===
void CarManager::displayCar(const Car &car) {
    std::cout << "----------------------------" << std::endl;
    std::cout << "RegNr: " << car.getRegNr().toStdString() << std::endl;
    std::cout << "Make: " << car.getMake().toStdString() << std::endl;
    std::cout << "Model: " << car.getModel().toStdString() << std::endl;
    std::cout << "Color: " << car.getColor().toStdString() << std::endl;
    std::cout << "Car type: " << car.getCarType().toStdString() << std::endl;
    std::cout << "Fuel type: " << car.getFuelType().toStdString() << std::endl;
    std::cout << "Year: " << car.getYear() << std::endl;
    std::cout << "Price: " << car.getPrice() << std::endl;
    std::cout << "Km driven: " << car.getKmDriven() << std::endl;
    std::cout << "Seats: " << car.getSeats() << std::endl;
    std::cout << "Available: " << (car.getAvailable() ? "Yes" : "No") << std::endl;
    std::cout << "----------------------------" << std::endl;
}

void CarManager::displayAllCars(const std::vector<Car> &cars) {
    std::cout << "============ All cars ===========" << std::endl;
    for (const auto &car : cars) {
        displayCar(car);
    }
    std::cout << "======================================" << std::endl;
}

