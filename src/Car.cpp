//
// Created by Albert on 17.04.2024.
//

#include "../include/Car.h"

// Constructor
Car::Car() {
    color = "Unknown";
    model = "Unknown";
    carType = "Unknown";
    year = 0;
    price = 0;
    kmDriven = 0;
    available = false;
}

Car::Car(std::string &color, std::string &model, std::string &carType, int year, int price, int kmDriven, int seats) {
    this->color = color;
    this->model = model;
    this->carType = carType;
    this->year = year;
    this->price = price;
    this->kmDriven = kmDriven;
    this->seats = seats;
    this->available = true;
}

// Destructor
Car::~Car() = default;

// Getters
std::string Car::getColor() const {return color;}
std::string Car::getModel() const {return model;}
std::string Car::getCarType() const {return carType;}
int Car::getYear() const {return year;}
int Car::getPrice() const {return price;}
int Car::getKmDriven() const {return kmDriven;}
bool Car::getAvailable() const {return available;}

// Setters
void Car::setColor(std::string color) {this->color = color;}
void Car::setPrice(int price) {this->price = price;}
void Car::setKmDriven(int kmDriven) {this->kmDriven = kmDriven;}
void Car::setAvailable(bool available) {this->available = available;}