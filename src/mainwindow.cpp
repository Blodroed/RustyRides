#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/Customer.h"
#include "../include/CustomerManager.h"
#include "../include/CustomerDialog.h"
#include "../include/Car.h"
#include "../include/CarManager.h"
#include "../include/CarDialog.h"
#include "../include/lease.h"
#include "../include/LeaseManager.h"
#include "../include/LeaseDialog.h"
#include "../include/editleasedialog.h"
#include "../include/areyousuredialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>

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

    // Table view of the customers
    ui->CustTable->setColumnCount(6);
    QStringList headers = {"Personal Number", "Email", "Phone", "Age", "Name", "Assigned Cars"};
    ui->CustTable->setHorizontalHeaderLabels(headers);
    ui->CustTable->horizontalHeader()->setStretchLastSection(true);

    // Table view of the cars
    ui->CarTable->setColumnCount(11);
    QStringList carHeaders = {"Reg Nr", "Make", "Model", "Color", "Car Type", "Fuel Type", "Year", "Price", "Km Driven", "Seats", "Available"};
    ui->CarTable->setHorizontalHeaderLabels(carHeaders);
    ui->CarTable->horizontalHeader()->setStretchLastSection(false);

    // Table view of the leases
    ui->LeaseTable->setColumnCount(8);
    QStringList leaseHeaders = {"LeaseID", "Reg Nr", "Person Nr", "Days of Lease", "Negotiated Price", "Total Price", "StartDate", "Open or Closed"};
    ui->LeaseTable->setHorizontalHeaderLabels(leaseHeaders);
    ui->LeaseTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->LeaseTable->horizontalHeader()->setStretchLastSection(true);

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

// Should also check if customer has any leases or cars

// TODO: similar stuff for cars and leases

// ==================== Leases Tab ====================
void MainWindow::updateLeaseTable() {
    ui->LeaseTable->setRowCount(0);
    qDebug() << "Updating table with lease count: " << leasesRef.size();

    for (size_t row = 0; row < leasesRef.size(); ++row) {
        const auto& lease = leasesRef[row];
        ui->LeaseTable->insertRow(row);

        qDebug() << "Setting row:" << row
                 << "LeaseId:" << lease.getleaseId()
                 << "RegNr:" << lease.getRegNr()
                 << "PersonNr:" << lease.getPersonNr()
                 << "Days of lease:" << lease.getDaysOfLease()
                 << "Negotiated price:" << lease.getNegotiatedPrice()
                 << "Total price:" << lease.getTotalPrice()
                 << "StartDate:" << lease.getStartDate()
                 << "Open or closed:" << lease.isOpenOrClosed();

        ui->LeaseTable->setItem(row, 0, new QTableWidgetItem(QString::number(lease.getleaseId())));
        ui->LeaseTable->setItem(row, 1, new QTableWidgetItem(lease.getRegNr()));
        ui->LeaseTable->setItem(row, 2, new QTableWidgetItem(lease.getPersonNr()));
        ui->LeaseTable->setItem(row, 3, new QTableWidgetItem(QString::number(lease.getDaysOfLease())));
        ui->LeaseTable->setItem(row, 4, new QTableWidgetItem(QString::number(lease.getNegotiatedPrice())));
        ui->LeaseTable->setItem(row, 5, new QTableWidgetItem(QString::number(lease.getTotalPrice())));
        ui->LeaseTable->setItem(row, 6, new QTableWidgetItem(lease.getStartDate()));
        ui->LeaseTable->setItem(row, 7, new QTableWidgetItem(lease.isOpenOrClosed() ? "Open" : "Closed"));
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

    // finding the car and customer objects related to the selected lease
    auto carFromLease = CarManager::searchForCarWithRegNr(carsRef, selectedLease->getRegNr());
    auto customerFromLease = CustomerManager::searchForCustomerWithPersonNr(customersRef, selectedLease->getPersonNr());

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
    if (confirmDialog.exec() == QDialog::Accepted) {
        LeaseManager::deleteLease(leasesRef, *selectedLease, jsonParser);
        updateLeaseTable();
    }
}
