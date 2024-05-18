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