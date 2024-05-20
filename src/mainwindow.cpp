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
#include "../include/areyousuredialog.h"

#include <QMessageBox>
#include <QTableWidgetItem>

MainWindow::MainWindow(JsonParser& jsonParser, std::vector<Customer>& customers, std::vector<Car>& cars, QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , jsonParser(jsonParser)
        , customersRef(customers)
        , carsRef(cars)
{
    ui->setupUi(this);

    // Table view of the customers
    // TODO: Similar table view for cars and leases

    ui->CustTable->setColumnCount(5);
    QStringList headers = {"Personal Number", "Email", "Phone", "Age", "Name"};
    ui->CustTable->setHorizontalHeaderLabels(headers);
    ui->CustTable->horizontalHeader()->setStretchLastSection(true);

    // Table view of the cars

    ui->CarTable->setColumnCount(11);
    QStringList carHeaders = {"Reg Nr", "Make", "Model", "Color", "Car Type", "Fuel Type", "Year", "Price", "Km Driven", "Seats", "Available"};
    ui->CarTable->setHorizontalHeaderLabels(carHeaders);
    ui->CarTable->horizontalHeader()->setStretchLastSection(false);

    // update relevant tables
    updateCustomerTable();
    updateCarTable();
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
    // TODO: add upcoming tables
}

// ==================== Customer window ====================
// Ever so slightly changed the function, as the row behavior was bugged

void MainWindow::updateCustomerTable() {
    ui->CustTable->setRowCount(0);

    qDebug() << "Updating table with customer count: " << customersRef.size();

    for (size_t row = 0; row < customersRef.size(); ++row) {
        const auto& customer = customersRef[row];
        ui->CustTable->insertRow(row);

        qDebug() << "Setting row:" << row
                 << "PN:" << customer.getPersonNr()
                 << "Email:" << customer.getEmail()
                 << "Phone:" << customer.getPhone()
                 << "Age:" << customer.getAge()
                 << "Name:" << customer.getName();

        ui->CustTable->setItem(row, 0, new QTableWidgetItem(customer.getPersonNr()));
        ui->CustTable->setItem(row, 1, new QTableWidgetItem(customer.getEmail()));
        ui->CustTable->setItem(row, 2, new QTableWidgetItem(customer.getPhone()));
        ui->CustTable->setItem(row, 3, new QTableWidgetItem(QString::number(customer.getAge())));
        ui->CustTable->setItem(row, 4, new QTableWidgetItem(customer.getName()));
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

    Customer& selectedCustomer = customersRef[currentRow];

    // This opens the same dialog window as "register new customer"
    // Values are pre-entered to easily know what you're changing

    CustomerDialog* customerDialog = new CustomerDialog(this);
    customerDialog->setPersonNr(selectedCustomer.getPersonNr());
    customerDialog->setEmail(selectedCustomer.getEmail());
    customerDialog->setPhone(selectedCustomer.getPhone());
    customerDialog->setAge(selectedCustomer.getAge());
    customerDialog->setName(selectedCustomer.getName());
    customerDialog->setModal(true);

    // Make the personNr field read-only
    customerDialog->getPersonNrLineEdit()->setReadOnly(true);

    if (customerDialog->exec() == QDialog::Accepted) {
        // Create a new Customer object with the updated data
        Customer updatedCustomer(customerDialog->getPersonNr(), customerDialog->getEmail(),
                                 customerDialog->getPhone(), customerDialog->getAge(),
                                 customerDialog->getName(), selectedCustomer.getAssignedCarsRegNr());

        // Call the editCustomer function
        CustomerManager::editCustomerAllInstances(selectedCustomer, updatedCustomer, jsonParser);
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

    AreYouSureDialog confirmDialog(this);
    if (confirmDialog.exec() == QDialog::Accepted) {
        CustomerManager::deleteCustomer(customersRef, &customersRef[currentRow], jsonParser);
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

void MainWindow::on_NewLeaseBtn_clicked() {
    LeaseDialog* leaseDialog = new LeaseDialog(carsRef, customersRef, this);
    leaseDialog->setModal(true);
    qDebug() << "Opened the lease dialog";
    if (leaseDialog->exec() == QDialog::Accepted) {
    }
    delete leaseDialog;
}
