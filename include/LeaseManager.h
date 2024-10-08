#ifndef HELLHUB_LEASEMANAGER_H
#define HELLHUB_LEASEMANAGER_H

#include "Car.h"
#include "Lease.h"
#include "Customer.h"
#include "JsonParser.h"

#include <vector>
#include <QString>


class LeaseManager {
public:
    // Lease manager functions
    static void createLease(std::vector<Lease> &leases, const Lease &newlease, JsonParser &jsonParser);
    static void editDaysOfLease(Lease &lease, int daysOfLease, JsonParser &jsonParser);
    static void editLease(Lease &lease, int daysOfLease, int negotiatedPrice, const QString &newStartDate, JsonParser &jsonParser);
    static void closeLease(Lease &lease, std::vector<Car> &cars, std::vector<Customer> &customers, JsonParser &jsonParser);
    static void deleteLease(std::vector<Lease> &leases, Lease &lease, JsonParser &jsonParser);

    // Lease search functions
    static Lease* searchForLeaseWithID(std::vector<Lease> &leases, const int id);
};


#endif //HELLHUB_LEASEMANAGER_H
