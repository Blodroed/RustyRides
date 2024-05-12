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
    void addCustomer(customer&& customer);
    const std::vector<customer>& getAllCustomers() const;
    void displayCustomer(const customer& customer) const;
    void displayAllCustomers() const;

private:
    std::vector<customer> customers; // To be moved to main eventually
};

#endif // HELLHUB_CUSTOMERMANAGER_H