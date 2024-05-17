#include "include/CustomerDialog.h"
#include "ui_customer.h"

CustomerDialog::CustomerDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::Customer)
{
    ui->setupUi(this);
}
