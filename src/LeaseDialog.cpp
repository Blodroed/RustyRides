#include "../include/LeaseDialog.h"
#include "ui_LeaseDialog.h"

#include <vector>

LeaseDialog::LeaseDialog(const std::vector<Car>& carsRef, const std::vector<Customer>& customerRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaseDialog)
    , carsRef(carsRef)
    , customerRef(customerRef)
{
    ui->setupUi(this);
}

LeaseDialog::~LeaseDialog()
{
    delete ui;
}

// getters
QString LeaseDialog::getPhoneNumber() const { return ui->CustomerPhone->text(); }
QString LeaseDialog::getCarType() const { return ui->CarTypeFilter->currentText(); }
QString LeaseDialog::getFuelType() const { return ui->FuelTypeFilter->currentText(); }
int LeaseDialog::getSeats() const { return ui->SeatCapacityFilter->text().toInt(); }
int LeaseDialog::getMinPrice() const { return ui->MinPrice->text().toInt(); }
int LeaseDialog::getMaxPrice() const { return ui->MaxPrice->text().toInt(); }
