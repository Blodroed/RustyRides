#include "../include/customer.h"
#include "ui_customer.h"


// Putting anything in the ("") fields below, makes it pre-entered in the dialogwindow

customer::customer(QWidget *parent)
    : QDialog(parent), ui(new Ui::customer) {
    ui->setupUi(this);
    setPersonNr("");
    setEmail("");
    setPhone("");
    setAge(0);
    setName("");
}

customer::customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name)
    : QDialog(nullptr), ui(new Ui::customer) {
    ui->setupUi(this);
    setPersonNr(personNr);
    setEmail(email);
    setPhone(phone);
    setAge(age);
    setName(name);
}

customer::customer(customer&& other) noexcept
: QDialog(nullptr), ui(other.ui),
personNr(std::move(other.personNr)),
email(std::move(other.email)),
phone(std::move(other.phone)),
age(other.age),
name(std::move(other.name)) {
    other.ui = nullptr;
    setParent(static_cast<QWidget*>(other.parent()));
}

customer& customer::operator=(customer&& other) noexcept {
if (this != &other) {
QDialog::setParent(static_cast<QWidget*>(other.parent()));
delete ui;
ui = other.ui;
other.ui = nullptr;

personNr = std::move(other.personNr);
email = std::move(other.email);
phone = std::move(other.phone);
age = other.age;
name = std::move(other.name);
}
return *this;
}

customer::~customer() {
    delete ui;
}

// A lot of back and forth to make these setters actually work. They are ugly though
// Long story short; making setters and getters work properly with the UI was less straightforward than I had hoped

void customer::setPersonNr(const QString &personNr) {
    this->personNr = personNr;
    if (ui->personalNumberLineEdit) {
        ui->personalNumberLineEdit->setText(personNr);
    }
}

void customer::setEmail(const QString &email) {
    this->email = email;
    if (ui->emailLineEdit) {
        ui->emailLineEdit->setText(email);
    }
}

void customer::setPhone(const QString &phone) {
    this->phone = phone;
    if (ui->phoneLineEdit) {
        ui->phoneLineEdit->setText(phone);
    }
}

// This one is a little weird but necessary to keep the input line empty

void customer::setAge(int age) {
    this->age = age;
    if (ui->ageLineEdit) {
        ui->ageLineEdit->setText(age > 0 ? QString::number(age) : "");
    }
}

void customer::setName(const QString &name) {
    this->name = name;
    if (ui->nameLineEdit) {
        ui->nameLineEdit->setText(name);
    }
}


// Getters
QString customer::getPersonNr() const { return ui->personalNumberLineEdit->text(); }
QString customer::getEmail() const { return ui->emailLineEdit->text(); }
QString customer::getPhone() const { return ui->phoneLineEdit->text(); }
int customer::getAge() const { return ui->ageLineEdit->text().isEmpty() ? 0 : ui->ageLineEdit->text().toInt(); }
QString customer::getName() const { return ui->nameLineEdit->text(); }
