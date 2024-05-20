//
// Created by Albert on 17.04.2024.
//
#include <QString>

#include "../include/Car.h"

// Constructor
Car::Car() {
    color = "Unknown";
    model = "Unknown";
    carType = "Unknown";
    year = 0;
    price = 0;
    seats = 0;
    kmDriven = 0;
    available = false;
}

Car::Car(const QString &regNr, const QString &make, const QString &model, const QString &color, const QString &carType,
         const QString &fuelType, const int year, const int price, const int kmDriven,
         const int seats, const bool available) {
    this->RegNr = regNr;
    this->make = make;
    this->model = model;
    this->color = color;
    this->carType = carType;
    this->fuelType = fuelType;
    this->year = year;
    this->price = price;
    this->kmDriven = kmDriven;
    this->seats = seats;
    this->available = available;
}

// Destructor
Car::~Car() = default;

// Getters
QString Car::getRegNr() const {return RegNr;}
QString Car::getMake() const {return make;}
QString Car::getModel() const {return model;}
QString Car::getColor() const {return color;}
QString Car::getCarType() const {return carType;}
QString Car::getFuelType() const {return fuelType;}
int Car::getSeats() const {return seats;}
int Car::getYear() const {return year;}
int Car::getPrice() const {return price;}
int Car::getKmDriven() const {return kmDriven;}
bool Car::getAvailable() const {return available;}

// Setters
void Car::setMake(const QString &make) {this->make = make;}
void Car::setModel(const QString &model) {this->model = model;}
void Car::setColor(const QString &color) {this->color = color;}
void Car::setCarType(const QString &carType) {this->carType = carType;}
void Car::setFuelType(const QString &fuelType) {this->fuelType = fuelType;}
void Car::setYear(const int year) {this->year = year;}
void Car::setPrice(const int price) {this->price = price;}
void Car::setKmDriven(const int newKmDriven) {this->kmDriven = newKmDriven;}
void Car::setSeats(const int newSeats) {this->seats = newSeats;}
void Car::setAvailable(const bool available) {this->available = available;}

