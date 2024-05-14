//
// Created by Marcus on 14.05.2024.
//

#include "../include/areyousuredialog.h"
#include "ui_areyousuredialog.h"

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
