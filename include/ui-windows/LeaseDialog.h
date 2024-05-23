//
// Created by Marcus on 15.05.2024.
//

#ifndef HELLHUB_LEASEDIALOG_H
#define HELLHUB_LEASEDIALOG_H

#include "../CarManager.h"
#include "../CustomerManager.h"
#include "../LeaseManager.h"

#include <vector>

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class LeaseDialog;
}
QT_END_NAMESPACE

class LeaseDialog : public QDialog
{
    Q_OBJECT

public:
    LeaseDialog(const std::vector<Car>& carsRef, const std::vector<Customer>& customerRef, QWidget *parent = nullptr);
    ~LeaseDialog();

    // getters
    Car getSelectedCar();
    Customer getSelectedCustomer();
    const int getDaysOfLease();
    const QString getDateTimeAsString();

private slots:
    void on_CustomerPhone_textChanged(const QString& phoneNumber);
    void on_FilteredCustomerTable_itemSelectionChanged();
    void on_FilteredCarTable_itemSelectionChanged();
    void filterCars();
    void on_leaseFromDateTimeEdit_dateChanged(const QDate& date);
    void on_leaseUntilDateTimeEdit_dateChanged(const QDate& date);

private:
    Ui::LeaseDialog *ui;

    // ref to the vectors in main.cpp
    const std::vector<Car>& carsRef;
    const std::vector<Customer>& customerRef;

    // filter vectors for creating new leases
    std::vector<Car> filteredCars;
    std::vector<Customer> filteredCustomers;

    // Selected car and customer
    Car selectedCar;
    Customer selectedCustomer;

    // lease class values
    //Lease newLease;

    // extra variables for lease info getters
    int daysOfLease;
};
#endif // HELLHUB_LEASEDIALOG_H
