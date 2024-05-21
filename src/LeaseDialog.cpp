#include "../include/LeaseDialog.h"
#include "ui_LeaseDialog.h"

#include <vector>
#include <QString>
#include <QLineEdit>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDateEdit>

LeaseDialog::LeaseDialog(std::vector<Car>& carsRef, std::vector<Customer>& customerRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaseDialog)
    , carsRef(carsRef)
    , customerRef(customerRef)
{
    ui->setupUi(this);

    // connect signals and slots for customer
    connect(ui->CustomerPhone, &QLineEdit::textChanged, this, &LeaseDialog::on_CustomerPhone_textChanged);

    // connect signals and slots for car


    // datetime picker
    connect(ui->leaseFromDateTimeEdit, &QDateEdit::dateChanged, this, &LeaseDialog::on_leaseFromDateTimeEdit_dateChanged);

    // Tableview for cars
    ui->FilteredCarTable->setColumnCount(10);
    QStringList carHeaders = {"Reg Nr", "Make", "Model", "Color", "Car Type", "Fuel Type", "Year", "Price", "Km Driven", "Seats"};
    ui->FilteredCarTable->setHorizontalHeaderLabels(carHeaders);
    ui->FilteredCarTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->FilteredCarTable->horizontalHeader()->setStretchLastSection(true);

    // ListView for customers
    ui->FilteredCustomerTable->setColumnCount(6);
    QStringList customerHeaders = {"Name", "Phone", "Email", "Age", "PersonNr", "Leases"};
    ui->FilteredCustomerTable->setHorizontalHeaderLabels(customerHeaders);
    ui->FilteredCustomerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->FilteredCustomerTable->horizontalHeader()->setStretchLastSection(true);

    // set minimum dates for date picker
    ui->leaseFromDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    ui->leaseUntilDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
}

LeaseDialog::~LeaseDialog()
{
    delete ui;
}

// ================== SLOTS ==================
// value changed slot
void LeaseDialog::on_CustomerPhone_textChanged(const QString& text) {
    qDebug() << "Text changed: " << text;
    // filter customers cleared
    filteredCustomers.clear();

    // This for loop compares phone in strict position from start to finish
    for (auto customerPtr : customerRef) {
        const QString& phone = customerPtr.getPhone();
        if (phone.startsWith(text)) {
            filteredCustomers.push_back(&customerPtr);
        }
    }

// the table is then updated with the matching customers
    ui->FilteredCustomerTable->setRowCount(0);
    for (const auto& customerPtr : filteredCustomers) {
        int row = ui->FilteredCustomerTable->rowCount();
        ui->FilteredCustomerTable->insertRow(row);
        ui->FilteredCustomerTable->setItem(row, 0, new QTableWidgetItem(customerPtr->getName()));
        ui->FilteredCustomerTable->setItem(row, 1, new QTableWidgetItem(customerPtr->getPhone()));
        ui->FilteredCustomerTable->setItem(row, 2, new QTableWidgetItem(customerPtr->getEmail()));
        ui->FilteredCustomerTable->setItem(row, 3, new QTableWidgetItem(QString::number(customerPtr->getAge())));
        ui->FilteredCustomerTable->setItem(row, 4, new QTableWidgetItem(customerPtr->getPersonNr()));
        QString tempCars;
        CustomerManager::getCarsFromCustomerAsString(*customerPtr, tempCars, carsRef);
        ui->FilteredCustomerTable->setItem(row, 5, new QTableWidgetItem(tempCars));
    }
}

// date changed slot
void LeaseDialog::on_leaseFromDateTimeEdit_dateChanged(const QDate& date) {
    qDebug() << "Date changed: " << date.addDays(+1);
    if (ui->leaseUntilDateTimeEdit->date() < date.addDays(+1)) {
        ui->leaseUntilDateTimeEdit->setDate(date.addDays(+1));
    }
}

// getters
QString LeaseDialog::getPhoneNumber() const { return ui->CustomerPhone->text(); }
QString LeaseDialog::getCarType() const { return ui->CarTypeFilter->currentText(); }
QString LeaseDialog::getFuelType() const { return ui->FuelTypeFilter->currentText(); }
int LeaseDialog::getSeats() const { return ui->SeatCapacityFilter->text().toInt(); }
int LeaseDialog::getMinPrice() const { return ui->MinPrice->text().toInt(); }
int LeaseDialog::getMaxPrice() const { return ui->MaxPrice->text().toInt(); }
