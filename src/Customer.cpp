#include "../include/customer.h"
#include "ui_customer.h"


/**
 * @brief Constructs a new customer dialog with a parent.
 * @param parent The widget that will be the parent of this dialog.
 *
 * This constructor initializes the UI and sets default values for customer details.
 */
customer::customer(QWidget *parent)
        : QDialog(parent), ui(new Ui::customer),
          personNr("Unknown"), email("Unknown"), phone("Unknown"), age(0), name("Unknown")
{
    ui->setupUi(this);
}

/**
 * @brief Constructs a customer dialog with detailed information.
 * @param personNr The personal number of the customer.
 * @param email The email address of the customer.
 * @param phone The phone number of the customer.
 * @param age The age of the customer.
 * @param name The full name of the customer.
 *
 * This constructor initializes the UI and sets the customer details to the provided values.
 */
customer::customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name)
        : QDialog(nullptr), ui(new Ui::customer),
          personNr(personNr), email(email), phone(phone), age(age), name(name)
{
    ui->setupUi(this);
    ui->personalNumberLineEdit->setText(this->personNr);
    ui->emailLineEdit->setText(this->email);
    ui->phoneLineEdit->setText(this->phone);
    ui->ageLineEdit->setText(QString::number(this->age));
    ui->nameLineEdit->setText(this->name);
}

/**
 * @brief Destructor for the customer dialog.
 *
 * Cleans up the UI resources.
 */
customer::~customer() {
    delete ui;
}

/**
 * @brief Move constructor.
 * @param other Another customer object to move data from.
 *
 * Moves the customer details and UI from another instance to this one.
 */
customer::customer(customer&& other) noexcept :
QDialog(nullptr), ui(new Ui::customer),
personNr(std::move(other.personNr)),
email(std::move(other.email)),
phone(std::move(other.phone)),
age(other.age),
name(std::move(other.name))
{
    ui->setupUi(this);
    other.ui = nullptr;
}

/**
 * @brief Move assignment operator.
 * @param other Another customer object to assign from.
 * @return A reference to this instance.
 *
 * Moves the customer details and UI from another instance to this one and ensures proper cleanup.
 */
customer& customer::operator=(customer&& other) noexcept {
if (this != &other) {
personNr = std::move(other.personNr);
email = std::move(other.email);
phone = std::move(other.phone);
age = other.age;
name = std::move(other.name);

delete ui;
ui = other.ui;
other.ui = nullptr;
}
return *this;
}

// Setters
void customer::setPersonNr(const QString &personNr) { this->personNr = personNr; }
void customer::setEmail(const QString &email) { this->email = email; }
void customer::setPhone(const QString &phone) { this->phone = phone; }
void customer::setAge(int age) { this->age = age; }
void customer::setName(const QString &name) { this->name = name; }

// Getters
QString customer::getPersonNr() const { return personNr; }
QString customer::getEmail() const { return email; }
QString customer::getPhone() const { return phone; }
int customer::getAge() const { return age; }
QString customer::getName() const { return name; }
