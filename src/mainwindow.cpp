#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/customer.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Similar functions will need to be implemented for all buttons in the program.
void MainWindow::on_NewCustBtn_clicked() {
    customer* customerDialog = new customer(this);
    customerDialog->setModal(true);
    if (customerDialog->exec() == QDialog::Accepted) {

        // Some short documentation to explain (all of this was missing before);
        // The lines below allow the UI to access the private parts ( :-) ) of the customer class
        // Values are received from whatever is typed into the matching fields in the UI
        // The customer is then created and moved to the vector in the manager class
        // Which is made possible by the addCustomer function.

        QString personNr = customerDialog->getPersonNr();
        QString email = customerDialog->getEmail();
        QString phone = customerDialog->getPhone();
        int age = customerDialog->getAge();
        QString name = customerDialog->getName();

        customer newCustomer(personNr, email, phone, age, name);
        custManager.addCustomer(std::move(newCustomer));
    }

    delete customerDialog;
}
