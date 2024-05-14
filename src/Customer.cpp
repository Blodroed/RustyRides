//
// Created by Marcus on 10.05.2024.
//

#include "../include/Customer.h"
#include "ui_customer.h"

// Putting anything in the ("") fields below, makes it pre-entered in the dialogwindow

Customer::Customer(QWidget *parent)
    : QDialog(parent), ui(new Ui::Customer), regNr("") {
    ui->setupUi(this);
    setPersonNr("");
    setEmail("");
    setPhone("");
    setAge(0);
    setName("");
}

Customer::Customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name)
    : QDialog(nullptr), ui(new Ui::Customer), regNr("") {
    ui->setupUi(this);
    setPersonNr(personNr);
    setEmail(email);
    setPhone(phone);
    setAge(age);
    setName(name);
}

// Minor change here (less use of std::move)

Customer::Customer(Customer&& other) noexcept
: QDialog(nullptr), ui(new Ui::Customer), regNr(other.regNr) {
    ui->setupUi(this);
    setParent(static_cast<QWidget*>(other.parent()));

    setPersonNr(other.getPersonNr());
    setEmail(other.getEmail());
    setPhone(other.getPhone());
    setAge(other.getAge());
    setName(other.getName());
}

Customer& Customer::operator=(Customer&& other) noexcept {
if (this != &other) {
QDialog::setParent(static_cast<QWidget*>(other.parent()));

setPersonNr(other.getPersonNr());
    setEmail(other.getEmail());
    setPhone(other.getPhone());
    setAge(other.getAge());
    setName(other.getName());
    regNr = other.regNr;
}
return *this;
}

Customer::~Customer() {
    delete ui;
}

// A lot of back and forth to make these setters actually work. They are ugly though
// Long story short; making setters and getters work properly with the UI was less straightforward than I had hoped

void Customer::setPersonNr(const QString &personNr) {
    this->personNr = personNr;
    if (ui->personalNumberLineEdit) {
        ui->personalNumberLineEdit->setText(personNr);
    }
}

void Customer::setEmail(const QString &email) {
    this->email = email;
    if (ui->emailLineEdit) {
        ui->emailLineEdit->setText(email);
    }
}

void Customer::setPhone(const QString &phone) {
    this->phone = phone;
    if (ui->phoneLineEdit) {
        ui->phoneLineEdit->setText(phone);
    }
}

// This one is a little weird but necessary to keep the input line empty

void Customer::setAge(int age) {
    this->age = age;
    if (ui->ageLineEdit) {
        ui->ageLineEdit->setText(age > 0 ? QString::number(age) : "");
    }
}

void Customer::setName(const QString &name) {
    this->name = name;
    if (ui->nameLineEdit) {
        ui->nameLineEdit->setText(name);
    }
}

void customer::setRegNr(const QString &regNr) {
    this->regNr = regNr;
}

void Customer::assignCar(const Car* car) {
    assignedCars.push_back(car->getRegNr());
}


// Getters
QString Customer::getPersonNr() const { return ui->personalNumberLineEdit->text(); }
QString Customer::getEmail() const { return ui->emailLineEdit->text(); }
QString Customer::getPhone() const { return ui->phoneLineEdit->text(); }
int Customer::getAge() const { return ui->ageLineEdit->text().isEmpty() ? 0 : ui->ageLineEdit->text().toInt(); }
QString Customer::getName() const { return ui->nameLineEdit->text(); }
QString customer::getRegNr() const { return regNr; }
