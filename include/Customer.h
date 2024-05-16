//
// Created by Marcus on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMER_H
#define HELLHUB_CUSTOMER_H


#include <QString>
#include <vector>

#include "../include/Car.h"

class Customer {
public:
    // Constructor
    Customer();
    explicit Customer(const QString &personNr, const QString &email, const QString &phone, int age,
                      const QString &name, const std::vector<QString> &assignedCarsRegNr);

    // Destructor
    virtual ~Customer();

    // Setters
    void setPersonNr(const QString &personNr);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setAge(int age);
    void setName(const QString &name);
    void assignCar(const Car &car);

    // Getters
    QString getPersonNr() const;
    QString getEmail() const;
    QString getPhone() const;
    int getAge() const;
    QString getName() const;

private:
    QString personNr;
    QString email;
    QString phone;
    int age;
    QString name;

    std::vector<QString> assignedCarsRegNr;
};

#endif //HELLHUB_CUSTOMER_H
