//
// Created by Albert on 18.05.2024.
//

#include "../include/Lease.h"

// init static variable
int Lease::lastLeaseId = 0;

// creation of new lease constructor
Lease::Lease(const QString &regNr, const QString &personNr, const QString &startDate, const int daysOfLease, const int negotiatedPrice)
            : Lease(++lastLeaseId, regNr, personNr, startDate, daysOfLease, negotiatedPrice, negotiatedPrice * daysOfLease, true) {}

// import from database constructor
Lease::Lease(const int id, const QString &regNr, const QString &personNr, const QString &startDate, const int daysOfLease, const int negotiatedPrice,
             const int totalPrice, const bool openOrClosed)
             : leaseId(id), regNr(regNr), personNr(personNr), startDate(startDate),
               daysOfLease(daysOfLease), negotiatedPrice(negotiatedPrice), totalPrice(totalPrice),
               openOrClosed(openOrClosed) {
    if (id > lastLeaseId) lastLeaseId = id;
}

// getters
int Lease::getleaseId() const { return leaseId; }
QString Lease::getRegNr() const { return regNr; }
QString Lease::getPersonNr() const { return personNr; }
QString Lease::getStartDate() const { return startDate; }
int Lease::getDaysOfLease() const { return daysOfLease; }
int Lease::getNegotiatedPrice() const { return negotiatedPrice; }
int Lease::getTotalPrice() const { return totalPrice; }
bool Lease::isOpenOrClosed() const { return openOrClosed; }

// setters
void Lease::setDaysOfLease(int newDaysOfLease) {
    daysOfLease = newDaysOfLease;
    totalPrice = daysOfLease * negotiatedPrice;
}
void Lease::setNegotiatedPrice(int newNegotiatedPrice) {
    negotiatedPrice = newNegotiatedPrice;
    totalPrice = daysOfLease * negotiatedPrice;
}
void Lease::setStartDate(const QString &newStartDate) { startDate = newStartDate; }

void Lease::setOpenOrClosed(bool newOpenOrClosed) { openOrClosed = newOpenOrClosed; }