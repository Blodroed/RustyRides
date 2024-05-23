//
// Created by Albert on 18.05.2024.
//

#include "../include/LeaseManager.h"

void LeaseManager::createLease(std::vector<Lease> &leases, const Lease &newLease, JsonParser &jsonParser) {
    leases.push_back(newLease);
    jsonParser.exportSingleLeaseToJson(newLease);
}

void LeaseManager::editDaysOfLease(Lease &lease, int daysOfLease, JsonParser &jsonParser) {
    lease.setDaysOfLease(daysOfLease);
    jsonParser.editSingleLeaseToJson(lease);
}

void LeaseManager::editLease(Lease &lease, int daysOfLease, int negotiatedPrice, const QString &newStartDate, JsonParser &jsonParser) {
    lease.setDaysOfLease(daysOfLease);
    lease.setNegotiatedPrice(negotiatedPrice);
    lease.setStartDate(newStartDate);
    jsonParser.editSingleLeaseToJson(lease);
}

void LeaseManager::closeLease(Lease &lease, std::vector<Car> &cars, std::vector<Customer> &customers,
                              JsonParser &jsonParser) {
    lease.setOpenOrClosed(false);
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

void LeaseManager::deleteLease(std::vector<Lease> &leases, Lease &lease, JsonParser &jsonParser) {
    for (auto it = leases.begin(); it != leases.end(); ++it) {
        if (it->getleaseId() == lease.getleaseId()) {
            leases.erase(it);
            break;
        }
    }
    jsonParser.deleteSingleLeaseFromJson(lease);
}

Lease* LeaseManager::searchForLeaseWithID(std::vector<Lease> &leases, const int id) {
    for (auto &lease : leases) {
        if (lease.getleaseId() == id) {
            return &lease;
        }
    }
    return nullptr;
}
