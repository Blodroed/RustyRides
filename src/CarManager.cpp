//
// Created by Albert on 22.04.2024.
//

#include "../include/CarManager.h"
#include "../include/Car.h"
#include "../include/JsonParser.h"
#include <iostream>
#include <vector>

void CarManager::createCar(std::vector<Car> &cars, const Car &newCar,JsonParser &jsonParser) {
    // passing the car to the json document
    jsonParser.exportSingleCarToJson(newCar);

    // taking the reference of the vector cars and adding the car to it
    cars.push_back(newCar);
}

void CarManager::displayCar(const Car &car) {
    std::cout << "========================" << std::endl;
    std::cout << "Car info" << std::endl;
    std::cout << "-------------------" << std::endl;
    std::cout << "RegNr: " << car.getRegNr().toStdString() << std::endl;
    std::cout << "Color: " << car.getColor().toStdString() << std::endl;
    std::cout << "Model: " << car.getModel().toStdString() << std::endl;
    std::cout << "Car type: " << car.getCarType().toStdString() << std::endl;
    std::cout << "Fuel type: " << car.getFuelType().toStdString() << std::endl;
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
    std::cout << "=== All cars =====================" << std::endl;
    for (const auto &car : cars) {
        std::cout << "----------------------------" << std::endl;
        std::cout << "RegNr: " << car.getRegNr().toStdString()
                  << ", Color: " << car.getColor().toStdString()
                  << ", Model: " << car.getModel().toStdString()
                  << ", Car type: " << car.getCarType().toStdString()
                  << ", Fuel type: " << car.getFuelType().toStdString()
                  << ", Year: " << car.getYear()
                  << ", Price: " << car.getPrice()
                  << ", Km driven: " << car.getKmDriven() << std::endl;
        if (car.getAvailable()) {
            std::cout << "Available: Yes" << std::endl;
        } else {
            std::cout << "Available: No" << std::endl;
        }
    }
    std::cout << "=================================" << std::endl;
}

Car* CarManager::searchForCarWithRegNR(std::vector<Car> &cars, const QString &regNr) {
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
/**
 * @brief Edits the attributes of a Car object.
 *
 * This function edits the attributes of a Car object based on the attributes of another Car object.
 * The function checks if the registration numbers of the two cars match before editing.
 * If the registration numbers do not match, the function does not perform any edits and prints an error message.
 * If the Car pointer is null, the function does not perform any edits and prints an error message.
 *
 * @param car A pointer to the Car object to be edited.
 * @param editedCar A reference to a Car object containing the new attributes.
 */
void CarManager::editCarObject(Car *car, Car &editedCar) {

    if (car == nullptr) {
        std::cout << "Car pointer is not pointing to anything" << std::endl;
        return;
    }

    if (car->getRegNr() == editedCar.getRegNr()) {
        car->setColor(editedCar.getColor());
        car->setModel(editedCar.getModel());
        car->setCarType(editedCar.getCarType());
        car->setFuelType(editedCar.getFuelType());
        car->setYear(editedCar.getYear());
        car->setPrice(editedCar.getPrice());
        car->setKmDriven(editedCar.getKmDriven());
        car->setSeats(editedCar.getSeats());
        car->setAvailable(editedCar.getAvailable());

        std::cout << "Car object edited" << std::endl;
        return;
    } else {
        std::cout << "The regNr of the car object and the edited car object do not match" << std::endl;
    }
}

void CarManager::editCarAllInstances(Car *car, Car &editedCar, JsonParser &jsonParser) {
    /*
     * In the function we take a reference to the car we want to edit
     * We then iterate through the vector cars and compare the regNr of each car with the regNr of the provided car
     * If the regNr is found we edit the car object in the vector cars
     * We then export the edited car to the json document
     */
    if (car == nullptr) {
        std::cout << "Car pointer is not pointing to anything" << std::endl;
        return;
    }

    // editing the car object
    editCarObject(car, editedCar);

    // exporting the edited car to the json document,
    // remember that we are dereferencing the car pointer before passing it to the function
    // TODO: maybe make exportSingleCarToJson take a pointer instead of a reference
    jsonParser.editSingleCarToJson(*car);
}

void CarManager::deleteCar(std::vector<Car> &cars, Car *car, JsonParser &jsonParser) {
    /*
     * This function is used to delete a car object from the vector cars
     * The function takes a reference to the vector cars and a pointer to the car object
     * The function iterates through the vector cars and compares the regNr of each car with the regNr of the provided car
     * If the regNr is found the function deletes the car object from the vector cars
     */
    if (car == nullptr) {
        std::cout << "Car pointer is not pointing to anything" << std::endl;
        return;
    }

    if (car->getAvailable() == false) {
        // this should probably also be checked in the remove button in the relevant menu
        std::cout << "Car is rented, you cannot remove it" << std::endl;
        return;
    }

    jsonParser.deleteSingleCarFromJson(car);

    for (auto it = cars.begin(); it != cars.end(); ++it) {
        if (it->getRegNr() == car->getRegNr()) {
            cars.erase(it);
            std::cout << "Car deleted" << std::endl;
            return;
        }
    }
}

void CarManager::availabilitySwitch(Car *car) {
    if (car->getAvailable()) {
        car->setAvailable(false);
    } else {
        car->setAvailable(true);
    }
}

