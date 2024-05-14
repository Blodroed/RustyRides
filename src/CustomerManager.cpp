//
// Created by Marcus on 10.05.2024.
//

#include "../include/customermanager.h"
#include <QDebug>

customerManager::customerManager() {}

void customerManager::addCustomer(Customer&& customer) {
    customers.push_back(std::move(customer));

    // Part of the debug code when the tableview wasn't working properly
    qDebug() << "Added Customer. Total now: " << customers.size();
}

std::vector<customer>& customerManager::getAllCustomers() {
    return customers;
}

// Removed functions that served no purpose