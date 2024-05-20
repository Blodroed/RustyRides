#include "LeaseDialog.h"
#include "./ui_LeaseDialog.h"

LeaseDialog::LeaseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LeaseDialog)
{
    ui->setupUi(this);
}

LeaseDialog::~LeaseDialog()
{
    delete ui;
}
