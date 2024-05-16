//
// Created by Marcus on 10.05.2024.
//

#include "../include/customermanager.h"
#include <QDebug>

void CustomerManager::createCustomer(std::vector<Customer> &customers, const Customer &newCustomer, JsonParser &jsonParser) {
    jsonParser.exportSingleCustomerToJson(newCustomer);

    customers.push_back(newCustomer);
}

// Removed functions that served no purpose
