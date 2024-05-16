//
// Created by Marcus on 10.05.2024.
//

#include "../include/customermanager.h"
#include <QDebug>
#include <iostream>

void CustomerManager::createCustomer(std::vector<Customer> &customers, const Customer &newCustomer, JsonParser &jsonParser) {
    // export the newly created customer to the json file
    jsonParser.exportSingleCustomerToJson(newCustomer);

    // add the customer to the vector
    customers.push_back(newCustomer);
}

void CustomerManager::deleteCustomer(std::vector<Customer> &customers, Customer *customer, JsonParser &jsonParser) {
    if (customer == nullptr) {
        std::cout << "Customer not found";
        return;
    }

    if (!customer->getAssignedCarsRegNr().empty()) {
        // this can be changed to execute a dialog in the future
        std::cout << "Customer has assigned cars. Please close lease agreements before deleting the customer";
        return;
    }

    jsonParser.deleteSingleCustomerFromJson(*customer);

    // remove the customer from the vector
    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (&(*it) == customer) {
            customers.erase(it);
            std::cout << "Customer deleted" << std::endl;
            return;
        }
    }
}

std::vector<const Customer*> CustomerManager::searchForCustomerWithSeveralParameters(const std::vector<Customer> &customers,
                                                                           Customer &searchCustomer) {
    // creating a pointer vector to found customers
    std::vector<const Customer*> foundCustomers;

    // comparing the searchCustomer with all customers in the vector
    // the customer is added if the searchCustomer has the same values as the customer
    // or the searchCustomer has corresponding empty values
    for (const auto &customer : customers) {
        if ((searchCustomer.getPersonNr().isEmpty() || customer.getPersonNr() == searchCustomer.getPersonNr()) &&
            (searchCustomer.getEmail().isEmpty() || customer.getEmail() == searchCustomer.getEmail()) &&
            (searchCustomer.getPhone().isEmpty() || customer.getPhone() == searchCustomer.getPhone()) &&
            (searchCustomer.getAge() == 0 || customer.getAge() == searchCustomer.getAge()) &&
            (searchCustomer.getName().isEmpty() || customer.getName() == searchCustomer.getName())) {
            foundCustomers.push_back(&customer);
        }
    }
    return foundCustomers;
}

void CustomerManager::assignCarToCustomer(Customer &customer, const Car &car, JsonParser &jsonParser) {
    customer.assignCar(car.getRegNr());
    jsonParser.editSingleCustomerToJson(customer);
}

void CustomerManager::removeCarFromCustomer(Customer &customer, const Car &car, JsonParser &jsonParser) {
    customer.removeCar(car.getRegNr());
    jsonParser.editSingleCustomerToJson(customer);
}