//
// Created by Marcus on 10.05.2024.
//
#include <QString>
#include <vector>

#include "../include/Customer.h"


Customer::Customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name, const std::vector<QString> &assignedCarsRegNr)
{
    this->personNr = personNr;
    this->email = email;
    this->phone = phone;
    this->age = age;
    this->name = name;
    for (const auto& regNr : assignedCarsRegNr) {
        this->assignedCarsRegNr.push_back(regNr);
    }
}

// destructor
Customer::~Customer() = default;

// Setters
void Customer::setPersonNr(const QString &personNr) { this->personNr; }
void Customer::setEmail(const QString &email) { this->email; }
void Customer::setPhone(const QString &phone) { this->phone; }
void Customer::setAge(int age) { this->age; }
void Customer::setName(const QString &name) { this->name; }
void Customer::assignCar(const Car &car) { assignedCarsRegNr.push_back(car.getRegNr()); }


// Getters
QString Customer::getPersonNr() const { return personNr; }
QString Customer::getEmail() const { return email; }
QString Customer::getPhone() const { return phone; }
int Customer::getAge() const { return age; }
QString Customer::getName() const { return name; }
std::vector<QString> Customer::getAssignedCarsRegNr() const { return assignedCarsRegNr; }
