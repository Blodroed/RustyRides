#ifndef LEASEDIALOG_H
#define LEASEDIALOG_H

#include "CarManager.h"
#include "CustomerManager.h"

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
    QString getPhoneNumber() const;
    QString getCarType() const;
    QString getFuelType() const;
    int getSeats() const;
    int getMinPrice() const;
    int getMaxPrice() const;

private slots:
    void on_CustomerPhone_textChanged(const QString& phoneNumber);

private:
    Ui::LeaseDialog *ui;

    // ref to the vectors in main.cpp
    const std::vector<Car>& carsRef;
    const std::vector<Customer>& customerRef;

    // filter vectors for creating new leases
    std::vector<Car> filteredCars;
    std::vector<Customer> filteredCustomers;
};
#endif // LEASEDIALOG_H
