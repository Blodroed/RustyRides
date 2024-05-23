#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/CustomerManager.h"
#include "../include/CustomerDialog.h"
#include "../include/Car.h"
#include "../include/CarManager.h"
#include "../include/CarDialog.h"
#include "../include/LeaseManager.h"
#include "../include/LeaseDialog.h"
#include "../include/editleasedialog.h"
#include "../include/areyousuredialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDateTime>
#include <QFileDialog>

MainWindow::MainWindow(JsonParser& jsonParser, std::vector<Customer>& customers, std::vector<Car>& cars, std::vector<Lease>& leases, QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , jsonParser(jsonParser)
        , customersRef(customers)
        , carsRef(cars)
        , leasesRef(leases)
{
    // window setup
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Car Rental System");

    // ---- Table view of the customers ----
    ui->CustTable->setColumnCount(6);
    QStringList headers = {"Personal Number", "Email", "Phone", "Age", "Name", "Assigned Cars"};
    ui->CustTable->setHorizontalHeaderLabels(headers);
    ui->CustTable->horizontalHeader()->setStretchLastSection(false);
    // This will format the headers to fill the available white space
    for (int i = 0; i < ui->CustTable->horizontalHeader()->count(); ++i) {
        ui->CustTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // ---- Table view of the cars ----
    ui->CarTable->setColumnCount(11);
    QStringList carHeaders = {"Reg Nr", "Make", "Model", "Color", "Car Type", "Fuel Type", "Year", "Price", "Km Driven", "Seats", "Available"};
    ui->CarTable->setHorizontalHeaderLabels(carHeaders);
    ui->CarTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->CarTable->horizontalHeader()->setStretchLastSection(false);
    // format the headers to fill the available white space
    for (int i = 0; i < ui->CarTable->horizontalHeader()->count(); ++i) {
        ui->CarTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    // ---- Table view of the leases ----
    ui->LeaseTable->setColumnCount(9);
    QStringList leaseHeaders = {"LeaseID", "Reg Nr", "Customer Name", "Customer Tlf", "Days of Lease", "Negotiated Price", "Total Price", "StartDate", "State"};
    ui->LeaseTable->setHorizontalHeaderLabels(leaseHeaders);
    ui->LeaseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->LeaseTable->horizontalHeader()->setStretchLastSection(false);

    // ---- Slot connections for import and export buttons ----
    connect(ui->actionImport, &QAction::triggered, this, &MainWindow::importAction);
    connect(ui->actionExport, &QAction::triggered, this, &MainWindow::exportAction);

    // update relevant tables
    updateCustomerTable();
    updateCarTable();
    updateLeaseTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== Tab switching ====================
void MainWindow::on_tabWidget_currentChanged(int index) {
    // Update the tables
    updateCustomerTable();
    updateCarTable();
    updateLeaseTable();
}

// ==================== Customer window ====================
// Ever so slightly changed the function, as the row behavior was bugged

void MainWindow::updateCustomerTable() {
    ui->CustTable->setRowCount(0);

    qDebug() << "Updating table with customer count: " << customersRef.size();

    for (size_t row = 0; row < customersRef.size(); ++row) {
        const auto& customer = customersRef[row];
        ui->CustTable->insertRow(row);

        QString carsAsString;
        CustomerManager::getCarsFromCustomerAsString(customer, carsAsString);

        qDebug() << "Setting row:" << row
                 << "PN:" << customer.getPersonNr()
                 << "Email:" << customer.getEmail()
                 << "Phone:" << customer.getPhone()
                 << "Age:" << customer.getAge()
                 << "Name:" << customer.getName()
                 << "Assigned Cars:" << customer.getAssignedCarsRegNr().size();

        // hidden personNr for selecting the customer
        QTableWidgetItem* item = new QTableWidgetItem(customer.getPersonNr());
        item->setData(Qt::UserRole, customer.getPersonNr()); // Store personNummer as hidden data
        ui->CustTable->setItem(row, 0, item);

        ui->CustTable->setItem(row, 0, item);
        ui->CustTable->setItem(row, 1, new QTableWidgetItem(customer.getEmail()));
        ui->CustTable->setItem(row, 2, new QTableWidgetItem(customer.getPhone()));
        ui->CustTable->setItem(row, 3, new QTableWidgetItem(QString::number(customer.getAge())));
        ui->CustTable->setItem(row, 4, new QTableWidgetItem(customer.getName()));
        ui->CustTable->setItem(row, 5, new QTableWidgetItem(carsAsString));
    }
}

// Register new Customer (opens a dialog window)

void MainWindow::on_NewCustBtn_clicked() {
    CustomerDialog* customerDialog = new CustomerDialog(this);
    customerDialog->setModal(true);
    customerDialog->setWindowTitle("Register new customer");
    if (customerDialog->exec() == QDialog::Accepted) {

        QString personNr = customerDialog->getPersonNr();

        // Check if the personNr already exists
        Customer* existingCustomer = CustomerManager::searchForCustomerWithPersonNr(customersRef, personNr);
        if (existingCustomer != nullptr) {
            QMessageBox::warning(this, "Error", "Customer with this person-id already exists");
            qDebug() << "Customer with personNr already exists";
            delete customerDialog;
            return;
        }

        QString email = customerDialog->getEmail();
        QString phone = customerDialog->getPhone();
        int age = customerDialog->getAge();
        QString name = customerDialog->getName();

        // One of several debug steps implemented to find out why the tableview didn't work properly
        // Not really necessary anymore, but I'll leave it in should problems reoccur
        // Alternatively if similar debug output is necessary for cars and leases

        qDebug() << "Fetched from dialog - Person Number:" << personNr;
        qDebug() << "Fetched from dialog - Email:" << email;
        qDebug() << "Fetched from dialog - Phone:" << phone;
        qDebug() << "Fetched from dialog - Age:" << age;
        qDebug() << "Fetched from dialog - Name:" << name;

        Customer newCustomer(personNr, email, phone, age, name, {});
        CustomerManager::createCustomer(customersRef, newCustomer, jsonParser);
        updateCustomerTable();
    }

    delete customerDialog;
}

// Edit customer (opens a dialog window)

void MainWindow::on_EdtCustBtn_clicked() {
    int currentRow = ui->CustTable->currentRow();
    if (currentRow < 0) {
        qDebug() << "No customer selected for editing";
        return;
    }

    QString personNummer = ui->CustTable->item(currentRow, 0)->data(Qt::UserRole).toString();
    Customer *selectedCustomer = CustomerManager::searchForCustomerWithPersonNr(customersRef, personNummer);

    // This opens the same dialog window as "register new customer"
    // Values are pre-entered to easily know what you're changing

    CustomerDialog* customerDialog = new CustomerDialog(this);
    customerDialog->setWindowTitle("Edit Customer");
    customerDialog->setPersonNr(selectedCustomer->getPersonNr());
    customerDialog->setEmail(selectedCustomer->getEmail());
    customerDialog->setPhone(selectedCustomer->getPhone());
    customerDialog->setAge(selectedCustomer->getAge());
    customerDialog->setName(selectedCustomer->getName());
    customerDialog->setModal(true);

    // Make the personNr field read-only
    customerDialog->getPersonNrLineEdit()->setReadOnly(true);

    if (customerDialog->exec() == QDialog::Accepted) {
        // Create a new Customer object with the updated data
        Customer updatedCustomer(customerDialog->getPersonNr(), customerDialog->getEmail(),
                                 customerDialog->getPhone(), customerDialog->getAge(),
                                 customerDialog->getName(), selectedCustomer->getAssignedCarsRegNr());

        // Call the editCustomer function
        CustomerManager::editCustomerAllInstances(*selectedCustomer, updatedCustomer, jsonParser);
        // Update the table to reflect the changes
        updateCustomerTable();
    }

    delete customerDialog;
}

// Delete customer (opens "are you sure" dialog window)

void MainWindow::on_DelCustBtn_clicked() {
    int currentRow = ui->CustTable->currentRow();
    if (currentRow < 0) {
        return;
    }

    QString personNummer = ui->CustTable->item(currentRow, 0)->data(Qt::UserRole).toString();
    Customer *selectedCustomer = CustomerManager::searchForCustomerWithPersonNr(customersRef, personNummer);

    AreYouSureDialog confirmDialog(this);
    confirmDialog.setModal(true);
    confirmDialog.setWindowTitle("Delete Customer");
    if (confirmDialog.exec() == QDialog::Accepted) {
        CustomerManager::deleteCustomer(customersRef, selectedCustomer, jsonParser);
        updateCustomerTable();
    }
}

// ==================== Car window ====================

void MainWindow::updateCarTable() {
    ui->CarTable->setRowCount(0);
    qDebug() << "Updating table with car count: " << carsRef.size();

    for (size_t row = 0; row < carsRef.size(); ++row) {
        const auto& car = carsRef[row];
        ui->CarTable->insertRow(row);

        qDebug() << "Setting row:" << row
                 << "RegNr:" << car.getRegNr()
                 << "Make:" << car.getMake()
                 << "Model:" << car.getModel()
                 << "Color:" << car.getColor()
                 << "Car Type:" << car.getCarType()
                 << "Fuel Type:" << car.getFuelType()
                 << "Year:" << car.getYear()
                 << "Price:" << car.getPrice()
                 << "Km Driven:" << car.getKmDriven()
                 << "Seats:" << car.getSeats()
                 << "Available:" << car.getAvailable();

        ui->CarTable->setItem(row, 0, new QTableWidgetItem(car.getRegNr()));
        ui->CarTable->setItem(row, 1, new QTableWidgetItem(car.getMake()));
        ui->CarTable->setItem(row, 2, new QTableWidgetItem(car.getModel()));
        ui->CarTable->setItem(row, 3, new QTableWidgetItem(car.getColor()));
        ui->CarTable->setItem(row, 4, new QTableWidgetItem(car.getCarType()));
        ui->CarTable->setItem(row, 5, new QTableWidgetItem(car.getFuelType()));
        ui->CarTable->setItem(row, 6, new QTableWidgetItem(QString::number(car.getYear())));
        ui->CarTable->setItem(row, 7, new QTableWidgetItem(QString::number(car.getPrice())));
        ui->CarTable->setItem(row, 8, new QTableWidgetItem(QString::number(car.getKmDriven())));
        ui->CarTable->setItem(row, 9, new QTableWidgetItem(QString::number(car.getSeats())));
        ui->CarTable->setItem(row, 10, new QTableWidgetItem(car.getAvailable() ? "Yes" : "No"));
    }
}

// Register new car (opens a dialog window)

void MainWindow::on_NewCarBtn_clicked() {
    CarDialog* carDialog = new CarDialog(this);
    carDialog->setModal(true);
    carDialog->setWindowTitle("Register new car");
    if (carDialog->exec() == QDialog::Accepted) {

        QString regNr = carDialog->getRegNr();

        // Check if the regNr already exists
        Car* existingCar = CarManager::searchForCarWithRegNr(carsRef, regNr);
        if (existingCar != nullptr) {
            QMessageBox::warning(this, "Error", "Car with this registration number already exists");
            qDebug() << "Car with regNr already exists";
            delete carDialog;
            return;
        }

        QString make = carDialog->getMake();
        QString model = carDialog->getModel();
        QString color = carDialog->getColor();
        QString carType = carDialog->getCarType();
        QString fuelType = carDialog->getFuelType();
        int year = carDialog->getYear();
        int price = carDialog->getPrice();
        int kmDriven = carDialog->getKmDriven();
        int seats = carDialog->getSeats();
        bool available = carDialog->getAvailable();

        qDebug() << "Fetched from dialog - RegNr:" << regNr;
        qDebug() << "Fetched from dialog - Make:" << make;
        qDebug() << "Fetched from dialog - Model:" << model;
        qDebug() << "Fetched from dialog - Color:" << color;
        qDebug() << "Fetched from dialog - Car Type:" << carType;
        qDebug() << "Fetched from dialog - Fuel Type:" << fuelType;
        qDebug() << "Fetched from dialog - Year:" << year;
        qDebug() << "Fetched from dialog - Price:" << price;
        qDebug() << "Fetched from dialog - Km Driven:" << kmDriven;
        qDebug() << "Fetched from dialog - Seats:" << seats;
        qDebug() << "Fetched from dialog - Available:" << available;

        Car newCar(regNr, make, model, color,carType, fuelType, year, price, kmDriven, seats, available);
        CarManager::createCar(carsRef, newCar, jsonParser);
        updateCarTable();
    }
    delete carDialog;
}

// Edit Car (opens a dialog window)
// Similar to customer, values are pre entered for easy editing
void MainWindow::on_EdtCarBtn_clicked() {
    int currentRow = ui->CarTable->currentRow();
    if (currentRow < 0) {
        qDebug() << "No car selected for editing";
        return;
    } else if (ui->CarTable->item(currentRow, 10)->text() == "No") {
        qDebug() << "Cannot edit a car that is not available";

        // display error message box to client
        QMessageBox::warning(this, "Error", "Cannot edit a car that is not available");

        return;
    }

    // select car with regNr
    QString regNr = ui->CarTable->item(currentRow, 0)->text();
    Car* selectedCar = CarManager::searchForCarWithRegNr(carsRef, regNr);

    CarDialog* carDialog = new CarDialog(this);
    carDialog->setWindowTitle("Edit Car");

    // Populate dialog with car details
    carDialog->populateFields(*selectedCar);

    carDialog->setModal(true);

    // Make the regNr field read-only
    carDialog->getRegNrLineEdit()->setReadOnly(true);

    if (carDialog->exec() == QDialog::Accepted) {
        // Create a new Car object with the updated data
        Car updatedCar(carDialog->getRegNr(),
                       carDialog->getMake(),
                       carDialog->getModel(),
                       carDialog->getColor(),
                       carDialog->getCarType(),
                       carDialog->getFuelType(),
                       carDialog->getYear(),
                       carDialog->getPrice(),
                       carDialog->getKmDriven(),
                       carDialog->getSeats(),
                       carDialog->getAvailable());

        // Call the editCar function
        CarManager::editCarAllInstances(selectedCar, updatedCar, jsonParser);

        // Update the table to reflect the changes
        updateCarTable();
    }

    delete carDialog;
}

// Delete car (opens "are you sure" dialog window)

void MainWindow::on_DelCarBtn_clicked() {
    int currentRow = ui->CarTable->currentRow();
    if (currentRow < 0) {
        return;
    } else if (ui->CarTable->item(currentRow, 10)->text() == "No") {
        qDebug() << "Cannot delete a car that is not available";

        // display error message box to client
        QMessageBox::warning(this, "Error", "Cannot delete a car that is not available");

        return;
    }

    // select car with regNr
    QString regNr = ui->CarTable->item(currentRow, 0)->text();
    Car* selectedCar = CarManager::searchForCarWithRegNr(carsRef, regNr);

    AreYouSureDialog confirmDialog(this);
    confirmDialog.setModal(true);
    confirmDialog.setWindowTitle("Delete Car");
    if (confirmDialog.exec() == QDialog::Accepted) {
        CarManager::deleteCar(carsRef, selectedCar, jsonParser);
        updateCarTable();
    }
}

// ==================== Leases Tab ====================
void MainWindow::updateLeaseTable() {
    ui->LeaseTable->setRowCount(0);

    for (size_t row = 0; row < leasesRef.size(); row++) {
        const auto& lease = leasesRef[row];
        Car* car = CarManager::searchForCarWithRegNr(carsRef, lease.getRegNr());
        Customer* customer = CustomerManager::searchForCustomerWithPersonNr(customersRef, lease.getPersonNr());

        // car and customer var
        QString carRegNr = "Not found";
        QString customerName = "Not found";
        QString customerPhone = "Not found";

        if (car != nullptr) {
            carRegNr = car->getRegNr();
        }
        if (customer != nullptr) {
            customerName = customer->getName();
            customerPhone = customer->getPhone();
        }

        ui->LeaseTable->insertRow(row); // Insert a new row at the end of the table

        ui->LeaseTable->setItem(row, 0, new QTableWidgetItem(QString::number(lease.getleaseId())));
        ui->LeaseTable->setItem(row, 1, new QTableWidgetItem(carRegNr));
        ui->LeaseTable->setItem(row, 2, new QTableWidgetItem(customerName));
        ui->LeaseTable->setItem(row, 3, new QTableWidgetItem(customerPhone));
        ui->LeaseTable->setItem(row, 4, new QTableWidgetItem(QString::number(lease.getDaysOfLease())));
        ui->LeaseTable->setItem(row, 5, new QTableWidgetItem(QString::number(lease.getNegotiatedPrice())));
        ui->LeaseTable->setItem(row, 6, new QTableWidgetItem(QString::number(lease.getTotalPrice())));
        ui->LeaseTable->setItem(row, 7, new QTableWidgetItem(lease.getStartDate()));
        ui->LeaseTable->setItem(row, 8, new QTableWidgetItem(lease.isOpenOrClosed() ? "Open" : "Closed"));

        // Set the background color of the row to red if the lease is closed
        if (!lease.isOpenOrClosed()) {
            for (int i = 0; i < ui->LeaseTable->columnCount(); i++) {
                ui->LeaseTable->item(row, i)->setBackground(QBrush(QColor(255, 0, 0, 127)));
            }
        }

        // Set the background color of the row to green if the lease is open
        if (lease.isOpenOrClosed()) {
            for (int i = 0; i < ui->LeaseTable->columnCount(); i++) {
                ui->LeaseTable->item(row, i)->setBackground(QBrush(QColor(0, 255, 0, 127)));
            }
        }

        qDebug() << "Setting row:" << row
                 << "LeaseID:" << lease.getleaseId()
                 << "RegNr:" << lease.getRegNr()
                 << "Customer Name:" << customerName
                 << "Customer Tlf:" << customerPhone
                 << "Days of Lease:" << lease.getDaysOfLease()
                 << "Negotiated Price:" << lease.getNegotiatedPrice()
                 << "Total Price:" << lease.getTotalPrice()
                 << "StartDate:" << lease.getStartDate()
                 << "Open or Closed:" << (lease.isOpenOrClosed() ? "Open" : "Closed");
    }
}

void MainWindow::on_NewLeaseBtn_clicked() {
    LeaseDialog* leaseDialog = new LeaseDialog(carsRef, customersRef, this);
    leaseDialog->setModal(true);
    qDebug() << "Opened the lease dialog";
    if (leaseDialog->exec() == QDialog::Accepted) {
        Car selectedCar = leaseDialog->getSelectedCar();
        Customer selectedCustomer = leaseDialog->getSelectedCustomer();
        QString dateTimeAsString = leaseDialog->getDateTimeAsString();
        int daysOfLease = leaseDialog->getDaysOfLease();
        int totalPrice = selectedCar.getPrice() * daysOfLease;

        qDebug() << "Selected car: " << selectedCar.getRegNr();
        qDebug() << "Selected customer: " << selectedCustomer.getPersonNr();
        qDebug() << "Days of lease: " << daysOfLease;

        // Create a new lease
        Lease newLease(selectedCar.getRegNr(), selectedCustomer.getPersonNr(), dateTimeAsString, daysOfLease, totalPrice);
        LeaseManager::createLease(leasesRef, newLease, jsonParser);

        // Update the car and customer objects
        selectedCar.setAvailable(false);
        auto carToEdit = CarManager::searchForCarWithRegNr(carsRef, selectedCar.getRegNr());
        auto customerToEdit = CustomerManager::searchForCustomerWithPersonNr(customersRef, selectedCustomer.getPersonNr());

        CustomerManager::assignCarToCustomer(selectedCustomer, selectedCar, jsonParser);
        CarManager::editCarAllInstances(carToEdit, selectedCar, jsonParser);
        CustomerManager::editCustomerAllInstances(*customerToEdit, selectedCustomer, jsonParser);

        // Update the tables
        updateCarTable();
        updateCustomerTable();
        updateLeaseTable();
    }
    delete leaseDialog;
}

void MainWindow::on_EdtLeaseBtn_clicked() {
    int currentRow = ui->LeaseTable->currentRow();
    if (currentRow < 0) {
        qDebug() << "No lease selected for editing";
        return;
    } else if (ui->LeaseTable->item(currentRow, 7)->text() == "Closed") {
        qDebug() << "Cannot edit a closed lease";

        // display error message box to client
        QMessageBox::warning(this, "Error", "Cannot edit a closed lease");

        return;
    }

    // finding the selected lease in the original vector
    int leaseId = ui->LeaseTable->item(currentRow, 0)->text().toInt();
    Lease *selectedLease = LeaseManager::searchForLeaseWithID(leasesRef, leaseId);

    // finding the car and customer objects related to the selected lease
    auto carFromLease = CarManager::searchForCarWithRegNr(carsRef, selectedLease->getRegNr());
    auto customerFromLease = CustomerManager::searchForCustomerWithPersonNr(customersRef, selectedLease->getPersonNr());

    // creating and excecuting the dialog
    EditLeaseDialog* editLeaseDialog = new EditLeaseDialog(*carFromLease, *customerFromLease, *selectedLease, this);
    editLeaseDialog->setModal(true);
    editLeaseDialog->setWindowTitle("Edit Lease");

    if (editLeaseDialog->exec() == QDialog::Accepted) {
        int daysOfLease = editLeaseDialog->getNewDaysOfLease();
        int negotiatedPrice = editLeaseDialog->getNewNegotiatedPrice();
        QString newStartDate = editLeaseDialog->getNewStartDate();

        qDebug() << "Updated Lease:, " << selectedLease->getleaseId()
                << "Days of lease: " << daysOfLease
                << "Negotiated price: " << negotiatedPrice
                << "Total price: " << daysOfLease * negotiatedPrice
                << "Start date: " << newStartDate;

        LeaseManager::editLease(*selectedLease, daysOfLease, negotiatedPrice, newStartDate, jsonParser);

        // Update the tables
        updateLeaseTable();
        updateCarTable();
        updateCustomerTable();
    }
    delete editLeaseDialog;
}

void MainWindow::on_ClsLeaseBtn_clicked() {
    int currentRow = ui->LeaseTable->currentRow();
    if (currentRow < 0) {
        qDebug() << "No lease selected for closing";
        return;
    } else if (ui->LeaseTable->item(currentRow, 7)->text() == "Closed") {
        qDebug() << "Cannot close a closed lease";

        // display error message box to client
        QMessageBox::warning(this, "Error", "Cannot close a closed lease");

        return;
    }

    int leaseId = ui->LeaseTable->item(currentRow, 0)->text().toInt();
    Lease *selectedLease = LeaseManager::searchForLeaseWithID(leasesRef, leaseId);

    if (selectedLease == nullptr) {
        qDebug() << "No lease selected for closing";
        return;
    } else if (QDateTime::fromString(selectedLease->getStartDate(), Qt::ISODate) > QDateTime::currentDateTime()) {
        qDebug() << "Cannot close a lease that has not started yet";

        // display error message box to client
        QMessageBox::warning(this, "Error", "Cannot close a lease that has not started yet");

        return;
    }

    // finding the car and customer objects related to the selected lease
    auto carFromLease = CarManager::searchForCarWithRegNr(carsRef, selectedLease->getRegNr());
    auto customerFromLease = CustomerManager::searchForCustomerWithPersonNr(customersRef, selectedLease->getPersonNr());

    // get enddatetime of the lease
    QDateTime startDateTime = QDateTime::fromString(selectedLease->getStartDate(), Qt::ISODate);
    QDateTime endDateTime = startDateTime.addDays(selectedLease->getDaysOfLease());
    int daysSinceStart = startDateTime.daysTo(QDateTime::currentDateTime());

    // check if enddatetime is before current datetime or after
    if (endDateTime < QDateTime::currentDateTime()) {
        qDebug() << "The end date of the lease is before the current date";

        // display error message box to client
        QMessageBox::StandardButton reply;
        QString message = QString("The end date of the lease is before the current date. The lease has been extended by %1 days. The new total price is %2. Do you want to extend the lease?")
                .arg(daysSinceStart)
                .arg(selectedLease->getTotalPrice());
        reply = QMessageBox::question(this, "Close Lease", message, QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            LeaseManager::editDaysOfLease(*selectedLease, daysSinceStart, jsonParser);
            qDebug() << "Lease extended by " << daysSinceStart << " days";
        }
    } else if (endDateTime > QDateTime::currentDateTime()) {
        qDebug() << "The end date of the lease is after the current date";

        // display error message box to client
        QMessageBox::StandardButton reply;
        QString message = QString("The end date of the lease is after the current date. The lease has been shortened by %1 days. The new total price is %2. Do you want to shorten the lease?")
                .arg(daysSinceStart)
                .arg(selectedLease->getTotalPrice());
        reply = QMessageBox::question(this, "Close Lease", message, QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            LeaseManager::editDaysOfLease(*selectedLease, daysSinceStart, jsonParser);
            qDebug() << "Lease shortened by " << daysSinceStart << " days";
        }

    } else {
        qDebug() << "The end date of the lease is today";
    }

    // creating the lease dialog and converting to close
    EditLeaseDialog* editLeaseDialog = new EditLeaseDialog(*carFromLease, *customerFromLease, *selectedLease, this);

    // setup changing some values
    editLeaseDialog->setModal(true);
    editLeaseDialog->convertToCloseDialog();

    if (editLeaseDialog->exec() == QDialog::Accepted) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Close Lease", "Are you sure you want to close this lease? And has the customer returned the car?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            LeaseManager::closeLease(*selectedLease, carsRef, customersRef, jsonParser);

            QMessageBox::StandardButton replyKmDriven;
            replyKmDriven = QMessageBox::question(this, "Close Lease", "Do you want to update the km driven for the car?",
                                      QMessageBox::Yes|QMessageBox::No);
            if (replyKmDriven == QMessageBox::Yes) {
                CarDialog* carDialog = new CarDialog(this);
                carDialog->setModal(true);
                carDialog->setWindowTitle("Update km driven for car");

                // setup changing some values
                carDialog->convertToCloseDialog();

                // populate with selectedCar info
                carDialog->populateFields(*carFromLease);

                if (carDialog->exec() == QDialog::Accepted) {
                    int newKmDriven = carDialog->getKmDriven();
                    carFromLease->setKmDriven(newKmDriven);
                    CarManager::editCarAllInstances(carFromLease, *carFromLease, jsonParser);
                }
            }

            // Update the tables
            updateLeaseTable();
            updateCarTable();
            updateCustomerTable();
        }
    }
    delete editLeaseDialog;
}

void MainWindow::on_DelLeaseBtn_clicked() {
    int currentRow = ui->LeaseTable->currentRow();
    if (currentRow < 0) {
        qDebug() << "No lease selected for deletion";
        return;
    } else if (ui->LeaseTable->item(currentRow, 7)->text() == "Open") {
        qDebug() << "Cannot delete an open lease";

        // display error message box to client
        QMessageBox::warning(this, "Error", "Cannot delete an open lease");

        return;
    }

    int leaseId = ui->LeaseTable->item(currentRow, 0)->text().toInt();
    Lease *selectedLease = LeaseManager::searchForLeaseWithID(leasesRef, leaseId);

    AreYouSureDialog confirmDialog(this);
    confirmDialog.setModal(true);
    confirmDialog.setWindowTitle("Delete Lease");
    if (confirmDialog.exec() == QDialog::Accepted) {
        LeaseManager::deleteLease(leasesRef, *selectedLease, jsonParser);
        updateLeaseTable();
    }
}

void MainWindow::importAction() {
    // Open a file dialog and get the selected file path
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open JSON File"), "", tr("JSON Files (*.json)"));

    // Check if a file was selected
    if (!filePath.isEmpty()) {
       QMessageBox::StandardButtons reply;
         reply = QMessageBox::question(this, "Import", "Are you sure you want to import data from this file?",
                                         QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                qDebug() << "Just A test" << filePath;
            }
    }
}

void MainWindow::exportAction() {
    // Open a file dialog and get the selected file path
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save JSON File"), "", tr("JSON Files (*.json)"));

    // Check if a file was selected
    if (!filePath.isEmpty()) {
        jsonParser.fullBackup(filePath.toStdString());
    }

    // display message box to client
    QMessageBox::information(this, "Export", "Exported data to " + filePath);
}
