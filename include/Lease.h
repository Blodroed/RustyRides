//
// Created by Albert on 18.05.2024.
//

#ifndef HELLHUB_LEASE_H
#define HELLHUB_LEASE_H

#include <QString>
#include <QDateTime>

class Lease {
private:
    int leaseId;
    QString regNr;          // registration number of car leased
    QString personNr;       // personal number of customer
    QDateTime startDate;    // start date of lease
    int daysOfLease;        // days of lease
    int totalPrice;         // car price * days of lease
    bool openOrClosed;      // 0 = open, 1 = closed
};


#endif //HELLHUB_LEASE_H
