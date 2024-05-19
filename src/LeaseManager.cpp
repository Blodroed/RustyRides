//
// Created by Alber on 18.05.2024.
//

#include "../include/LeaseManager.h"

void LeaseManager::createLease(Customer &customer, Car &car, QString &startDate, int daysOfLease, JsonParser &jsonParser) {
    Lease lease(car.getRegNr(), customer.getPersonNr(), startDate, daysOfLease, car.getPrice());
    jsonParser.addLease(lease);
}