#include "../include/customermanager.h"
#include <QDebug>

/**
 * @brief Default constructor for customerManager.
 *
 * Initializes an empty list of customers. This constructor is necessary for creating instances without
 * predefined data.
 */
customerManager::customerManager() {}

/**
 * @brief Adds a customer to the manager.
 *
 * This method takes an rvalue reference to a customer object, efficiently moving it
 * into the internal customer list without copying.
 * @param customer A temporary customer object to be added to the manager.
 */
void customerManager::addCustomer(customer&& customer) {
    customers.push_back(std::move(customer));
}

/**
 * @brief Displays a customer's details on the debug output.
 *
 * This function formats and prints the details of a single customer to the standard debug output
 * using Qt's debugging tools. This is a carryover from the prototype CLI and serves for demonstration
 * or debugging purposes.
 * @param customer The customer whose details are to be displayed.
 */
void customerManager::displayCustomer(const customer& customer) const {
    QString details = QString("Customer Details:\nPersonal Number: %1\nEmail: %2\nPhone: %3\nAge: %4\nName: %5")
            .arg(customer.getPersonNr())
            .arg(customer.getEmail())
            .arg(customer.getPhone())
            .arg(customer.getAge())
            .arg(customer.getName());
    qDebug() << details;
}

/**
 * @brief Displays all customers' details on the debug output.
 *
 * Iterates over the list of customers and displays each one using the displayCustomer method.
 * This method is also a carryover from the CLI prototype and primarily used for debugging or demonstration.
 */
void customerManager::displayAllCustomers() const {
    for (const auto& cust : customers) {
        displayCustomer(cust);
    }
}