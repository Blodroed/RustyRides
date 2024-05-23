#ifndef HELLHUB_CUSTOMERMANAGER_H
#define HELLHUB_CUSTOMERMANAGER_H

#include <vector>
#include "../include/Customer.h"
#include "../include/JsonParser.h"

class CustomerManager {
public:
    static void createCustomer(std::vector<Customer> &customers, const Customer &newCustomer, JsonParser &jsonParser);

    static void editCustomerObject(Customer &customer, Customer &editedCustomer);
    static void editCustomerAllInstances(Customer &customer, Customer &editedCustomer, JsonParser &jsonParser);
    static void deleteCustomer(std::vector<Customer> &customers, Customer *customer, JsonParser &jsonParser);

    // search functions
    static Customer* searchForCustomerWithPersonNr(std::vector<Customer> &customers, const QString &personNr);
    static std::vector<const Customer*> searchForCustomerWithSeveralParameters(const std::vector<Customer> &customers,
                                                                               Customer &searchCustomer);

    // cars array related functions
    static void getCarsFromCustomerAsString(const Customer &customer, QString &carsAsString);
    static void assignCarToCustomer(Customer &customer, const Car &car, JsonParser &jsonParser);
    static void removeCarFromCustomer(Customer &customer, const Car &car, JsonParser &jsonParser);

    // cli display functions
    static void displayCustomer(const Customer& customer);
    static void displayAllCustomers(const std::vector<Customer> &customers);
};

#endif //HELLHUB_CUSTOMERMANAGER_H
