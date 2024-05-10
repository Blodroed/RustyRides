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
    customerDialog->exec();

    if (customerDialog->result() == QDialog::Accepted) {
    }

    delete customerDialog;
}
