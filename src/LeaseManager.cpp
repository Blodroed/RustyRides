#include "../include/LeaseManager.h"
#include "../include/CustomerManager.h"

// ==== Lease Managing Functions ====
// creating a new lease and adding it to the vector and database
void LeaseManager::createLease(std::vector<Lease> &leases, const Lease &newLease, JsonParser &jsonParser) {
    leases.push_back(newLease);
    jsonParser.exportSingleLeaseToJson(newLease);
}

// edit the lease with new days of lease
void LeaseManager::editDaysOfLease(Lease &lease, int daysOfLease, JsonParser &jsonParser) {
    lease.setDaysOfLease(daysOfLease);
    jsonParser.editSingleLeaseToJson(lease);
}

// edit the lease with new negotiated price
void LeaseManager::editLease(Lease &lease, int daysOfLease, int negotiatedPrice, const QString &newStartDate, JsonParser &jsonParser) {
    lease.setDaysOfLease(daysOfLease);
    lease.setNegotiatedPrice(negotiatedPrice);
    lease.setStartDate(newStartDate);
    jsonParser.editSingleLeaseToJson(lease);
}

// close the lease and set the car to available
void LeaseManager::closeLease(Lease &lease, std::vector<Car> &cars, std::vector<Customer> &customers,
                              JsonParser &jsonParser) {
    lease.setOpenOrClosed(false);
    jsonParser.editSingleLeaseToJson(lease);
    Car* tempCar;

    // set car to available
    for (auto &car : cars) {
        if (car.getRegNr() == lease.getRegNr()) {
            car.setAvailable(true);
            jsonParser.editSingleCarToJson(car);
            tempCar = &car;
            break;
        }
    }

    // remove car from customer
    for (auto &customer : customers) {
        if (customer.getPersonNr() == lease.getPersonNr()) {
            CustomerManager::removeCarFromCustomer(customer, *tempCar, jsonParser);
            break;
        }
    }
}

// delete the lease from the vector and database
void LeaseManager::deleteLease(std::vector<Lease> &leases, Lease &lease, JsonParser &jsonParser) {
    for (auto it = leases.begin(); it != leases.end(); ++it) {
        if (it->getleaseId() == lease.getleaseId()) {
            leases.erase(it);
            break;
        }
    }
    jsonParser.deleteSingleLeaseFromJson(lease);
}

// ==== Search Functions ====
Lease* LeaseManager::searchForLeaseWithID(std::vector<Lease> &leases, const int id) {
    for (auto &lease : leases) {
        if (lease.getleaseId() == id) {
            return &lease;
        }
    }
    return nullptr;
}
