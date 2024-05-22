#ifndef EDITLEASEDIALOG_H
#define EDITLEASEDIALOG_H

#include "LeaseManager.h"
#include "JsonParser.h"
#include "CarManager.h"
#include "CustomerManager.h"

#include <QDialog>
#include <vector>

namespace Ui {
class EditLeaseDialog;
}

class EditLeaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditLeaseDialog(const Car& carRef, const Customer& customerRef, Lease& selectedLease, QWidget *parent = nullptr);
    ~EditLeaseDialog();

    // getters
    int getNewDaysOfLease() const;
    int getNewNegotiatedPrice() const;
    int getNewTotalPrice() const;
    QString getNewStartDate() const;

private slots:
    void on_leaseFromDateTimeEdit_dateChanged(const QDateTime &date);
    void on_leaseUntilDateTimeEdit_dateChanged(const QDateTime &date);
    void on_NegotiatedPriceBox_valueChanged(const int newValue);
private:
    // update tables
    void updateCustomerInfoTable();
    void updateCarInfoTable();

    Ui::EditLeaseDialog *ui;
    Lease& selectedLease;
    const Car& carRef;
    const Customer& customerRef;

    // new values
    int newDaysOfLease;
    int newNegotiatedPrice;
    int newTotalPrice;
    QString newStartDate;
};

#endif // EDITLEASEDIALOG_H
