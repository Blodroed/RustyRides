//
// Created by Albert on 18.05.2024.
//

#ifndef HELLHUB_LEASEMANAGER_H
#define HELLHUB_LEASEMANAGER_H

#include "Car.h"
#include "Lease.h"
#include "Customer.h"
#include "JsonParser.h"

#include <vector>
#include <QString>


class LeaseManager {
    static void createLease(Customer &customer, Car &car, QString &startDate, int daysOfLease, JsonParser &jsonParser);
    static void extendLease(Lease &lease, int daysOfLease, JsonParser &jsonParser);
    static void editLease(Lease &lease, int daysOfLease, int negotiatedPrice, JsonParser &jsonParser);
    static void closeLease(Lease &lease, std::vector<Car> &cars, std::vector<Customer> &customers, JsonParser &jsonParser);
};


#endif //HELLHUB_LEASEMANAGER_H
