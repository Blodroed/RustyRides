//
// Created by Marcus on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMER_H
#define HELLHUB_CUSTOMER_H

#include <QDialog>
#include <QString>
#include <vector>

#include "../include/Car.h"

namespace Ui {
    class Customer;
}

class Customer : public QDialog
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = nullptr);
    Customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name);

    // Move constructor and assignment operator
    Customer(Customer&& other) noexcept;
    Customer& operator=(Customer&& other) noexcept;

    Customer(const Customer& other) = delete;
    Customer& operator=(const Customer& other) = delete;

    ~Customer();

    // Setters
    void setPersonNr(const QString &personNr);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setAge(int age);
    void setName(const QString &name);
    void setRegNr(const QString &regNr);
    void assignCar(const Car* car);

    // Getters
    QString getPersonNr() const;
    QString getEmail() const;
    QString getPhone() const;
    int getAge() const;
    QString getName() const;
    QString getRegNr() const;

private:
    Ui::Customer *ui;
    QString personNr;
    QString email;
    QString phone;
    int age;
    QString name;
    QString regNr;

    std::vector<std::string> assignedCars;
};

#endif //HELLHUB_CUSTOMER_H
