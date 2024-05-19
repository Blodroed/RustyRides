//
// Created by Albert on 18.05.2024.
//

#include "../include/Lease.h"

// creation of new lease constructor
Lease::Lease(QString &regNr, QString &personNr, QString &startDate, int daysOfLease, int negotiatedPrice)
            : Lease(++lastLeaseId, regNr, personNr, startDate, daysOfLease, negotiatedPrice, negotiatedPrice * daysOfLease, false) {}

// import from database constructor
Lease::Lease(int id, QString &regNr, QString &personNr, QString &startDate, int daysOfLease, int negotiatedPrice,
             int totalPrice, bool openOrClosed)
             : leaseId(id), regNr(regNr), personNr(personNr), startDate(startDate),
               daysOfLease(daysOfLease), negotiatedPrice(negotiatedPrice), totalPrice(totalPrice),
               openOrClosed(openOrClosed) {}

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
void Lease::setOpenOrClosed(bool newOpenOrClosed) { openOrClosed = newOpenOrClosed; }