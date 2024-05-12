#include "../include/customermanager.h"
#include <QDebug>

customerManager::customerManager() {}

void customerManager::addCustomer(customer&& customer) {
    customers.push_back(std::move(customer));

    // Part of the debug code when the tableview wasn't working properly
    qDebug() << "Added customer. Total now: " << customers.size();
}

const std::vector<customer>& customerManager::getAllCustomers() const {
    return customers;
}

// Removed functions that served no purpose