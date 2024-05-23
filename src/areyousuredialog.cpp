#include "../include/areyousuredialog.h"
#include "ui-design-files/ui_areyousuredialog.h"

AreYouSureDialog::AreYouSureDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AreYouSureDialog)
{
    ui->setupUi(this);
}

AreYouSureDialog::~AreYouSureDialog()
{
    delete ui;
}
