//
// Created by Marcu on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMERMANAGER_H
#define HELLHUB_CUSTOMERMANAGER_H

#include <vector>
#include "customer.h"

class customerManager {
public:
    customerManager();
    void addCustomer(Customer&& customer);
    const std::vector<Customer>& getAllCustomers() const;
    void displayCustomer(const Customer& customer) const;
    void displayAllCustomers() const;

private:
    std::vector<Customer> customers; // To be moved to main eventually
};

#endif // HELLHUB_CUSTOMERMANAGER_H