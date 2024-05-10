//
// Created by Marcu on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMERMANAGER_H
#define HELLHUB_CUSTOMERMANAGER_H

#include <vector>
#include "customer.h"

/**
 * @class CustomerManager
 * @brief Manages customer records.
 *
 * This class is responsible for managing a collection of customers.
 * It provides functionalities to add and display customers.
 */
class CustomerManager {
public:
    /**
     * @brief Default constructor for CustomerManager.
     *
     * Initializes a new instance of CustomerManager, setting up an empty list
     * of customers.
     */
    CustomerManager();

    /**
     * @brief Adds a customer to the manager.
     *
     * This function takes an rvalue reference to a customer object, moving it
     * into the customer list. This is intended to optimize memory by avoiding
     * unnecessary copies.
     * @param customer A temporary customer object to add to the manager.
     */
    void addCustomer(customer&& customer);

    /**
     * @brief Displays a customer's details.
     *
     * This function is a carryover from a prototype command line interface and
     * currently serves no operational purpose. It prints the details of a single
     * customer to the standard output.
     * @param customer The customer to display.
     */
    static void displayCustomer(const customer& customer) const; // making functions static void means we do not need to create an instance of the class to call them

    /**
     * @brief Displays all customers' details.
     *
     * This function is also a carryover from a prototype command line interface and
     * serves no operational purpose at the moment. It prints the details of all
     * customers managed by this instance to the standard output.
     */
    void displayAllCustomers() const;

private:
    std::vector<customer> customers; ///< A vector holding all managed customers.
};

#endif // HELLHUB_CUSTOMERMANAGER_H