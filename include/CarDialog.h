//
// Created by Marcus on 18.05.2024.
//

#ifndef HELLHUB_CARDIALOG_H
#define HELLHUB_CARDIALOG_H

#include "../include/cardialog.h"
#include "ui_cardialog.h"

CarDialog::CarDialog(QWidget *parent)
        : QDialog(parent)
        , ui(new Ui::CarDialog)
{
    ui->setupUi(this);
}

CarDialog::~CarDialog()
{
    delete ui;
}

// Setters for UI elements
void CarDialog::setRegNr(const QString& regNr) { ui->RegNrLineEdit->setText(regNr); }
void CarDialog::setMake(const QString& regNr) { ui->MakeLineEdit->setText(regNr); }
void CarDialog::setModel(const QString& model) { ui->ModelEdit->setText(model); }
void CarDialog::setColor(const QString& color) { ui->KmLineEdit->setText(color); }
void CarDialog::setCarType(const QString& carType) { ui->CarTypeEdit->setText(carType); }
void CarDialog::setFuelType(const QString& fuelType) { ui->FuelTypeEdit->setText(fuelType); }
void CarDialog::setYear(int year) { ui->YearEdit->setText(QString::number(year)); }
void CarDialog::setPrice(int price) { ui->PricePerDayLineEdit->setText(QString::number(price)); }
void CarDialog::setKmDriven(int kmDriven) { ui->KmLineEdit->setText(QString::number(kmDriven)); }
void CarDialog::setSeats(int seats) { ui->SeatsLineEdit->setText(QString::number(seats)); }
void CarDialog::setAvailable(bool available) {
    ui->availabilityCheckBox->setChecked(available);
}

// Getters for UI elements
QString CarDialog::getRegNr() const { return ui->RegNrLineEdit->text(); }
QString CarDialog::getMake() const { return ui->MakeLineEdit->text(); }
QString CarDialog::getModel() const { return ui->ModelEdit->text(); }
QString CarDialog::getColor() const { return ui->KmLineEdit->text(); }
QString CarDialog::getCarType() const { return ui->CarTypeEdit->text(); }
QString CarDialog::getFuelType() const { return ui->FuelTypeEdit->text(); }
int CarDialog::getYear() const { return ui->YearEdit->text().toInt(); }
int CarDialog::getPrice() const { return ui->PricePerDayLineEdit->text().toInt(); }
int CarDialog::getKmDriven() const { return ui->KmLineEdit->text().toInt(); }
int CarDialog::getSeats() const { return ui->SeatsLineEdit->text().toInt(); }
bool CarDialog::getAvailable() const {
    return ui->availabilityCheckBox->isChecked();
}

// Get the edit field for RegNr
QLineEdit* CarDialog::getRegNrLineEdit() const { return ui->MakeLineEdit; }



#endif //HELLHUB_CARDIALOG_H
