#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/Customer.h"
#include "../include/areyousuredialog.h"

MainWindow::MainWindow(JsonParser& jsonParser, std::vector<Customer>& customers, QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
        , jsonParser(jsonParser)
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
// Ever so slightly changed the function, as the row behavior was bugged

void MainWindow::updateCustomerTable() {
    ui->CustTable->setRowCount(0);

    auto& customers = custManager.getAllCustomers();
    qDebug() << "Updating table with customer count: " << customers.size();

    for (size_t row = 0; row < customers.size(); ++row) {
        const auto& customer = customers[row];
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
    Customer* customerDialog = new Customer(this);
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

        Customer newCustomer(personNr, email, phone, age, name, {});
        custManager.createCustomer(std::move(newCustomer));
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

    auto& customers = custManager.getAllCustomers();

    Customer& selectedCustomer = customers[currentRow];

    // This opens the same dialog window as "register new customer"
    // Values are pre-entered to easily know what you're changing

    Customer* customerDialog = new Customer(this);
    customerDialog->setPersonNr(selectedCustomer.getPersonNr());
    customerDialog->setEmail(selectedCustomer.getEmail());
    customerDialog->setPhone(selectedCustomer.getPhone());
    customerDialog->setAge(selectedCustomer.getAge());
    customerDialog->setName(selectedCustomer.getName());
    customerDialog->setModal(true);


    if (customerDialog->exec() == QDialog::Accepted) {
        selectedCustomer.setPersonNr(customerDialog->getPersonNr());
        selectedCustomer.setEmail(customerDialog->getEmail());
        selectedCustomer.setPhone(customerDialog->getPhone());
        selectedCustomer.setAge(customerDialog->getAge());
        selectedCustomer.setName(customerDialog->getName());

        // jsoParser.

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

        auto& customers = custManager.getAllCustomers();
        customers.erase(customers.begin() + currentRow);
        updateCustomerTable();
    }
}

// Should also check if customer has any leases or cars

// TODO: similar stuff for cars and leases
