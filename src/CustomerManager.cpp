#include "../include/customermanager.h"
#include <QDebug>
#include <iostream>

// ==== Customer manager functions ====
// creating a new customer
void CustomerManager::createCustomer(std::vector<Customer> &customers, const Customer &newCustomer, JsonParser &jsonParser) {
    // export the newly created customer to the json file
    jsonParser.exportSingleCustomerToJson(newCustomer);

    // add the customer to the vector
    customers.push_back(newCustomer);
}

// deleting a customer
void CustomerManager::deleteCustomer(std::vector<Customer> &customers, Customer *customer, JsonParser &jsonParser) {
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

// editing a customer
void CustomerManager::editCustomerObject(Customer &customer, Customer &editedCustomer) {
    // editing the customer object
    if (customer.getPersonNr() == editedCustomer.getPersonNr()) {
        customer = editedCustomer;
    } else {
        std::cout << "The personNr of the customer object and the edited customer object do not match" << std::endl;
    }
}

// this function makes sure it edits in both the program and the database
void CustomerManager::editCustomerAllInstances(Customer &customer, Customer &editedCustomer, JsonParser &jsonParser) {
    // editing the customer object
    editCustomerObject(customer, editedCustomer);

    // exporting the edited customer to the json document
    jsonParser.editSingleCustomerToJson(editedCustomer);
}

// Function searches for a customer with a personNr and returns a pointer to the customer
Customer* CustomerManager::searchForCustomerWithPersonNr(std::vector<Customer> &customers, const QString &personNr) {
    // returns nullpointer if the customer is not found
    for (auto &customer : customers) {
        if (customer.getPersonNr() == personNr) {
            return &customer;
        }
    }
    qDebug() << "Customer not found with: " << personNr;
    return nullptr;
}

// Function searches for a customer with several parameters and returns a vector of pointers to the found customers
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

// Function returns the vector of cars assigned to the customer
void CustomerManager::getCarsFromCustomerAsString(const Customer &customer, QString &carsAsString) {
    // creating a string of all cars assigned to the customer
    for (const auto &carRegNr : customer.getAssignedCarsRegNr()) {
        carsAsString.append(carRegNr);
        carsAsString.append(", ");
    }
}

// === Car assignment functions ===
void CustomerManager::assignCarToCustomer(Customer &customer, const Car &car, JsonParser &jsonParser) {
    customer.assignCar(car.getRegNr());
    jsonParser.editSingleCustomerToJson(customer);
}

void CustomerManager::removeCarFromCustomer(Customer &customer, const Car &car, JsonParser &jsonParser) {
    customer.removeCar(car.getRegNr());
    jsonParser.editSingleCustomerToJson(customer);
}

// ==== CLI related output functions ====
void CustomerManager::displayCustomer(const Customer &customer) {
    // displaying the customer
    std::cout << "----------------------------------------------------" << std::endl;
    std::cout << "PersonNr: " << customer.getPersonNr().toStdString()
              << ", Email: " << customer.getEmail().toStdString()
              << ", Phone: " << customer.getPhone().toStdString()
              << ", Age: " << customer.getAge()
              << ", Name: " << customer.getName().toStdString() << std::endl;
    std::cout << "Assigned cars: ";
    for (const auto &car : customer.getAssignedCarsRegNr()) {
        std::cout << car.toStdString() << ", ";
    }
    std::cout << std::endl;
    std::cout << "----------------------------------------------------" << std::endl;
}

void CustomerManager::displayAllCustomers(const std::vector<Customer> &customers) {
    // displaying all customers
    std::cout << "============ All customers ===========" << std::endl;
    for (const auto &customer : customers) {
        displayCustomer(customer);
    }
    std::cout << "======================================" << std::endl;
}