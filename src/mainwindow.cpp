#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/customer.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Table view of the customers
    // TODO: Similar table view for cars and leases

    ui->CustTable->setColumnCount(5);
    QStringList headers = {"Personal Number", "Email", "Phone", "Age", "Name"};
    ui->CustTable->setHorizontalHeaderLabels(headers);
    ui->CustTable->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ==================== Customer window ====================

void MainWindow::updateCustomerTable() {
    ui->CustTable->setRowCount(0);

    const auto& customers = custManager.getAllCustomers();
    qDebug() << "Updating table with customer count: " << customers.size();
    for (const auto& customer : customers) {
        int row = ui->CustTable->rowCount();
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

// Register new customer (dialogwindow)

void MainWindow::on_NewCustBtn_clicked() {
    customer* customerDialog = new customer(this);
    customerDialog->setModal(true);
    if (customerDialog->exec() == QDialog::Accepted) {

        QString personNr = customerDialog->getPersonNr();
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

        customer newCustomer(personNr, email, phone, age, name);
        custManager.addCustomer(std::move(newCustomer));
        updateCustomerTable(); // Refreshes/updates the tableview
    }

    delete customerDialog;
}

// TODO: Edit customer (dialogwindow and button functionality)
// TODO: Remove customer (simple "Are you sure?" dialogwindow, and button functionality)

// TODO: similar stuff for cars and leases
