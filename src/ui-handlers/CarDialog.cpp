#include <QIntValidator>
#include "../../include/ui-windows/CarDialog.h"
#include "../ui-design-files/ui_cardialog.h"

CarDialog::CarDialog(QWidget *parent)
        : QDialog(parent)
        , ui(new Ui::CarDialog)
{
    ui->setupUi(this);

    // set creation of car to be available by default
    ui->availabilityCheckBox->setChecked(true);

    // Create a new QIntValidator
    QIntValidator *intValidator = new QIntValidator(this);

    // Set the validator for the QLineEdit fields
    ui->YearEdit->setValidator(intValidator);
    ui->PricePerDayLineEdit->setValidator(intValidator);
    ui->KmLineEdit->setValidator(intValidator);
    ui->SeatsLineEdit->setValidator(intValidator);
}

CarDialog::~CarDialog()
{
    delete ui;
}

// Setters for UI elements
void CarDialog::setRegNr(const QString& regNr) { ui->RegNrLineEdit->setText(regNr); }
void CarDialog::setMake(const QString& regNr) { ui->MakeLineEdit->setText(regNr); }
void CarDialog::setModel(const QString& model) { ui->ModelEdit->setText(model); }
void CarDialog::setColor(const QString& color) { ui->ColorLineEdit->setText(color); }
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
QString CarDialog::getColor() const { return ui->ColorLineEdit->text(); }
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
QLineEdit* CarDialog::getRegNrLineEdit() const { return ui->RegNrLineEdit; }

// Convert to close dialog for editing km, setting all editable fields except km to read only
void CarDialog::convertToCloseDialog() {
    ui->RegNrLineEdit->setReadOnly(true);
    ui->MakeLineEdit->setReadOnly(true);
    ui->ModelEdit->setReadOnly(true);
    ui->ColorLineEdit->setReadOnly(true);
    ui->CarTypeEdit->setReadOnly(true);
    ui->FuelTypeEdit->setReadOnly(true);
    ui->YearEdit->setReadOnly(true);
    ui->PricePerDayLineEdit->setReadOnly(true);
    ui->SeatsLineEdit->setReadOnly(true);
    ui->availabilityCheckBox->setDisabled(true);
}

// Populate the dialog with car data
void CarDialog::populateFields(const Car &selectedCar) {
    ui->RegNrLineEdit->setText(selectedCar.getRegNr());
    ui->MakeLineEdit->setText(selectedCar.getMake());
    ui->ModelEdit->setText(selectedCar.getModel());
    ui->ColorLineEdit->setText(selectedCar.getColor());
    ui->CarTypeEdit->setText(selectedCar.getCarType());
    ui->FuelTypeEdit->setText(selectedCar.getFuelType());
    ui->YearEdit->setText(QString::number(selectedCar.getYear()));
    ui->PricePerDayLineEdit->setText(QString::number(selectedCar.getPrice()));
    ui->KmLineEdit->setText(QString::number(selectedCar.getKmDriven()));
    ui->SeatsLineEdit->setText(QString::number(selectedCar.getSeats()));
    ui->availabilityCheckBox->setChecked(selectedCar.getAvailable());
}
