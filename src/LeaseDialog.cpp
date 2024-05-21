#include "../include/LeaseDialog.h"
#include "../include/CarManager.h"
#include "../include/CustomerManager.h"
#include "ui_LeaseDialog.h"

#include <vector>
#include <QString>
#include <QLineEdit>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QDateEdit>
#include <QComboBox>
#include <QSpinBox>

LeaseDialog::LeaseDialog(const std::vector<Car>& carsRef, const std::vector<Customer>& customerRef, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaseDialog)
    , carsRef(carsRef)
    , customerRef(customerRef)
{
    ui->setupUi(this);

    // connect signals and slots for customer
    connect(ui->CustomerPhone, &QLineEdit::textChanged, this, &LeaseDialog::on_CustomerPhone_textChanged);

    // connect signals and slots for car
    connect(ui->CarTypeFilter, &QComboBox::currentTextChanged, this, &LeaseDialog::filterCars);
    connect(ui->FuelTypeFilter, &QComboBox::currentTextChanged, this, &LeaseDialog::filterCars);
    connect(ui->SeatCapacityFilter, &QSpinBox::valueChanged, this, &LeaseDialog::filterCars);
    connect(ui->MinPriceFilter, &QSpinBox::valueChanged, this, &LeaseDialog::filterCars);
    connect(ui->MaxPriceFilter, &QSpinBox::valueChanged, this, &LeaseDialog::filterCars);

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
// value phonenumber changed, slot
void LeaseDialog::on_CustomerPhone_textChanged(const QString& text) {
    qDebug() << "Text changed: " << text;
    // filter customers cleared
    filteredCustomers.clear();

    // This for loop compares phone in strict position from start to finish
    for (const auto& customer : customerRef) {
        const QString& phone = customer.getPhone();
        if (phone.startsWith(text)) {
            filteredCustomers.push_back(customer);
        }
    }

// the table is then updated with the matching customers
    ui->FilteredCustomerTable->setRowCount(0);
    for (const auto& customer : filteredCustomers) {
        int row = ui->FilteredCustomerTable->rowCount();
        ui->FilteredCustomerTable->insertRow(row);
        ui->FilteredCustomerTable->setItem(row, 0, new QTableWidgetItem(customer.getName()));
        ui->FilteredCustomerTable->setItem(row, 1, new QTableWidgetItem(customer.getPhone()));
        ui->FilteredCustomerTable->setItem(row, 2, new QTableWidgetItem(customer.getEmail()));
        ui->FilteredCustomerTable->setItem(row, 3, new QTableWidgetItem(QString::number(customer.getAge())));
        ui->FilteredCustomerTable->setItem(row, 4, new QTableWidgetItem(customer.getPersonNr()));
        QString tempCars;
        CustomerManager::getCarsFromCustomerAsString(customer, tempCars, carsRef);
        ui->FilteredCustomerTable->setItem(row, 5, new QTableWidgetItem(tempCars));
    }
}

// value carfilters changed, slot
void LeaseDialog::filterCars() {
    qDebug() << "Filtering cars";
    // filter cars cleared
    filteredCars.clear();

    // get the values from the filters
    QString bodyType = ui->CarTypeFilter->currentText().toLower();
    QString fuelType = ui->FuelTypeFilter->currentText().toLower();
    int seatCapacity = ui->SeatCapacityFilter->value();
    int minPrice = ui->MinPriceFilter->value();
    int maxPrice = ui->MaxPriceFilter->value();

    qDebug() << "Filtering cars: " << bodyType << " " << fuelType << " " << seatCapacity << " " << minPrice << " " << maxPrice;

    // This for loop compares the car filters with the cars in the vector
    for (auto& car : carsRef) {
        if (!car.getAvailable()) {
            continue;
        }

        if ((bodyType.isEmpty() || car.getCarType().toLower() == bodyType || bodyType == "-no cartype-") &&
            (fuelType.isEmpty() || car.getFuelType().toLower() == fuelType || fuelType == "-no fueltype-") &&
            (seatCapacity == 0 || car.getSeats() >= seatCapacity) &&
            (minPrice == 0 || car.getPrice() >= minPrice) &&
            (maxPrice == 0 || car.getPrice() <= maxPrice)) {
            filteredCars.push_back(car);
        }
    }

    // the table is then updated with the matching cars
    ui->FilteredCarTable->setRowCount(0);
    for (const auto& car : filteredCars) {
        int row = ui->FilteredCarTable->rowCount();
        ui->FilteredCarTable->insertRow(row);
        ui->FilteredCarTable->setItem(row, 0, new QTableWidgetItem(car.getRegNr()));
        ui->FilteredCarTable->setItem(row, 1, new QTableWidgetItem(car.getMake()));
        ui->FilteredCarTable->setItem(row, 2, new QTableWidgetItem(car.getModel()));
        ui->FilteredCarTable->setItem(row, 3, new QTableWidgetItem(car.getColor()));
        ui->FilteredCarTable->setItem(row, 4, new QTableWidgetItem(car.getCarType()));
        ui->FilteredCarTable->setItem(row, 5, new QTableWidgetItem(car.getFuelType()));
        ui->FilteredCarTable->setItem(row, 6, new QTableWidgetItem(QString::number(car.getYear())));
        ui->FilteredCarTable->setItem(row, 7, new QTableWidgetItem(QString::number(car.getPrice())));
        ui->FilteredCarTable->setItem(row, 8, new QTableWidgetItem(QString::number(car.getKmDriven())));
        ui->FilteredCarTable->setItem(row, 9, new QTableWidgetItem(QString::number(car.getSeats())));
    }
}

// value FromDate changed, slot
void LeaseDialog::on_leaseFromDateTimeEdit_dateChanged(const QDate& date) {
    qDebug() << "Date changed: " << date.addDays(+1);
    if (ui->leaseUntilDateTimeEdit->date() < date.addDays(+1)) {
        ui->leaseUntilDateTimeEdit->setDate(date.addDays(+1));
    }
}

// getters
Car LeaseDialog::getSelectedCar() {return selectedCar;}
Customer LeaseDialog::getSelectedCustomer() {return selectedCustomer;}
