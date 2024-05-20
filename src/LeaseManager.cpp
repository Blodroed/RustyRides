//
// Created by Alber on 18.05.2024.
//

#include "../include/LeaseManager.h"

void LeaseManager::createLease(Customer &customer, Car &car, QString &startDate, int daysOfLease, JsonParser &jsonParser) {
    Lease lease(car.getRegNr(), customer.getPersonNr(), startDate, daysOfLease, car.getPrice());
    jsonParser.exportSingleLeaseToJson(lease);
}

void LeaseManager::extendLease(Lease &lease, int daysOfLease, JsonParser &jsonParser) {
    lease.setDaysOfLease(daysOfLease);
    jsonParser.editSingleLeaseToJson(lease);
}

void LeaseManager::editLease(Lease &lease, int daysOfLease, int negotiatedPrice, JsonParser &jsonParser) {
    lease.setDaysOfLease(daysOfLease);
    lease.setNegotiatedPrice(negotiatedPrice);
    jsonParser.editSingleLeaseToJson(lease);
}

void LeaseManager::closeLease(Lease &lease, std::vector<Car> &cars, std::vector<Customer> &customers,
                              JsonParser &jsonParser) {
    lease.setOpenOrClosed(true);
    jsonParser.editSingleLeaseToJson(lease);

    // remove car from customer
    for (auto &customer : customers) {
        if (customer.getPersonNr() == lease.getPersonNr()) {
            customer.removeCar(lease.getRegNr());
            jsonParser.editSingleCustomerToJson(customer);
            break;
        }
    }

    // set car to available
    for (auto &car : cars) {
        if (car.getRegNr() == lease.getRegNr()) {
            car.setAvailable(true);
            jsonParser.editSingleCarToJson(car);
            break;
        }
    }
}