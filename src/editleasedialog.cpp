#include "../include/editleasedialog.h"
#include "ui_editleasedialog.h"

#include <QHeaderView>
#include <QTableWidgetItem>
#include <QString>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QSpinBox>

EditLeaseDialog::EditLeaseDialog(const Car& carRef, const Customer& customerRef, Lease& selectedLease, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditLeaseDialog)
    , selectedLease(selectedLease)
    , carRef(carRef)
    , customerRef(customerRef)
{
    ui->setupUi(this);
    // set old values in new values
    newDaysOfLease = selectedLease.getDaysOfLease();
    newNegotiatedPrice = selectedLease.getNegotiatedPrice();
    newTotalPrice = selectedLease.getTotalPrice();
    newStartDate = selectedLease.getStartDate();

    // connect signals and slots for datetime and price
    connect(ui->leaseFromDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &EditLeaseDialog::on_leaseFromDateTimeEdit_dateChanged);
    connect(ui->leaseUntilDateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &EditLeaseDialog::on_leaseUntilDateTimeEdit_dateChanged);
    connect(ui->NegotiatedPriceBox, &QSpinBox::valueChanged, this, &EditLeaseDialog::on_NegotiatedPriceBox_valueChanged);

    // Init CustomerInfo table
    ui->CustomerInfoTable->setColumnCount(6);
    QStringList customerHeaders = {"Name", "Phone", "Email", "Age", "PersonNr", "Leases"};
    ui->CustomerInfoTable->setHorizontalHeaderLabels(customerHeaders);
    ui->CustomerInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->CustomerInfoTable->horizontalHeader()->setStretchLastSection(true);
    updateCustomerInfoTable();

    // Init carinfo table
    ui->CarInfoTable->setColumnCount(10);
    QStringList carHeaders = {"Reg Nr", "Make", "Model", "Color", "Car Type", "Fuel Type", "Year", "Price", "Km Driven", "Seats"};
    ui->CarInfoTable->setHorizontalHeaderLabels(carHeaders);
    ui->CarInfoTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->CarInfoTable->horizontalHeader()->setStretchLastSection(false);
    updateCarInfoTable();

    // set startdate values
    ui->leaseFromDateTimeEdit->setDateTime(QDateTime::fromString(selectedLease.getStartDate(), Qt::ISODate));
    if (QDateTime::fromString(selectedLease.getStartDate(), Qt::ISODate) < QDateTime::currentDateTime()) {
        ui->leaseFromDateTimeEdit->setMinimumDateTime(QDateTime::fromString(selectedLease.getStartDate(), Qt::ISODate));
        ui->leaseFromDateTimeEdit->setReadOnly(true);
    } else {
        ui->leaseFromDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    }

    // set enddate values
    ui->leaseUntilDateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime());
    QDateTime leaseUntil = QDateTime::fromString(selectedLease.getStartDate(), Qt::ISODate).addDays(selectedLease.getDaysOfLease());
    ui->leaseUntilDateTimeEdit->setDateTime(leaseUntil);

    // Set price fields
    ui->NegotiatedPriceBox->setValue(selectedLease.getNegotiatedPrice());
    ui->TotalPriceLineEdit->setText(QString::number(selectedLease.getTotalPrice()));

}

EditLeaseDialog::~EditLeaseDialog()
{
    delete ui;
}

void EditLeaseDialog::updateCustomerInfoTable() {
    ui->CustomerInfoTable->setRowCount(1);
    ui->CustomerInfoTable->setItem(0, 0, new QTableWidgetItem(customerRef.getName()));
    ui->CustomerInfoTable->setItem(0, 1, new QTableWidgetItem(customerRef.getPhone()));
    ui->CustomerInfoTable->setItem(0, 2, new QTableWidgetItem(customerRef.getEmail()));
    ui->CustomerInfoTable->setItem(0, 3, new QTableWidgetItem(QString::number(customerRef.getAge())));
    ui->CustomerInfoTable->setItem(0, 4, new QTableWidgetItem(customerRef.getPersonNr()));
    QString tempCars;
    CustomerManager::getCarsFromCustomerAsString(customerRef, tempCars);
    ui->CustomerInfoTable->setItem(0, 5, new QTableWidgetItem(tempCars));
}

void EditLeaseDialog::updateCarInfoTable() {
    ui->CarInfoTable->setRowCount(1);
    ui->CarInfoTable->setItem(0, 0, new QTableWidgetItem(carRef.getRegNr()));
    ui->CarInfoTable->setItem(0, 1, new QTableWidgetItem(carRef.getMake()));
    ui->CarInfoTable->setItem(0, 2, new QTableWidgetItem(carRef.getModel()));
    ui->CarInfoTable->setItem(0, 3, new QTableWidgetItem(carRef.getColor()));
    ui->CarInfoTable->setItem(0, 4, new QTableWidgetItem(carRef.getCarType()));
    ui->CarInfoTable->setItem(0, 5, new QTableWidgetItem(carRef.getFuelType()));
    ui->CarInfoTable->setItem(0, 6, new QTableWidgetItem(QString::number(carRef.getYear())));
    ui->CarInfoTable->setItem(0, 7, new QTableWidgetItem(QString::number(carRef.getPrice())));
    ui->CarInfoTable->setItem(0, 8, new QTableWidgetItem(QString::number(carRef.getKmDriven())));
    ui->CarInfoTable->setItem(0, 9, new QTableWidgetItem(QString::number(carRef.getSeats())));
}

// slots
void EditLeaseDialog::on_leaseFromDateTimeEdit_dateChanged(const QDateTime &date) {
    newStartDate = date.toString(Qt::ISODate);
    newDaysOfLease = date.daysTo(ui->leaseUntilDateTimeEdit->dateTime());
    newTotalPrice = newNegotiatedPrice * newDaysOfLease;

    ui->TotalPriceLineEdit->setText(QString::number(newTotalPrice));
    ui->leaseUntilDateTimeEdit->setMinimumDateTime(date.addDays(1));
}

void EditLeaseDialog::on_leaseUntilDateTimeEdit_dateChanged(const QDateTime &date) {
    QDateTime leaseFrom = ui->leaseFromDateTimeEdit->dateTime();
    newDaysOfLease = leaseFrom.daysTo(date);
    newTotalPrice = newNegotiatedPrice * newDaysOfLease;
    ui->TotalPriceLineEdit->setText(QString::number(newNegotiatedPrice * newDaysOfLease));
}

void EditLeaseDialog::on_NegotiatedPriceBox_valueChanged(const int newValue) {
    newNegotiatedPrice = newValue;
    newTotalPrice = newValue * newDaysOfLease;
    ui->TotalPriceLineEdit->setText(QString::number(newTotalPrice));
}

// getters
int EditLeaseDialog::getNewDaysOfLease() const {return newDaysOfLease;}
int EditLeaseDialog::getNewNegotiatedPrice() const {return newNegotiatedPrice;}
int EditLeaseDialog::getNewTotalPrice() const {return newTotalPrice;}
QString EditLeaseDialog::getNewStartDate() const {return newStartDate;}
