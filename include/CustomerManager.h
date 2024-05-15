//
// Created by Marcus on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMERMANAGER_H
#define HELLHUB_CUSTOMERMANAGER_H

#include <vector>
#include "../include/Customer.h"

class customerManager {
public:
    customerManager();
    void addCustomer(Customer&& customer);
    std::vector<Customer>& getAllCustomers();
    void displayCustomer(const Customer& customer) const;
    void displayAllCustomers() const;

private:
    std::vector<Customer> customers; // To be moved to main eventually
};

#endif // HELLHUB_CUSTOMERMANAGER_H
