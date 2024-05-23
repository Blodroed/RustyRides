#include "../../include/ui-windows/CustomerDialog.h"
#include "../ui-design-files/ui_customerdialog.h"

CustomerDialog::CustomerDialog(QWidget *parent)
    : QDialog{parent}, ui{new Ui::CustomerDialog}
{
    ui->setupUi(this);
}

CustomerDialog::~CustomerDialog()
{
    delete ui;
}

// Setters for ui elements
void CustomerDialog::setPersonNr(const QString& personNr) { ui->personalNumberLineEdit->setText(personNr); }
void CustomerDialog::setEmail(const QString& email) { ui->emailLineEdit->setText(email); }
void CustomerDialog::setPhone(const QString& phone) { ui->phoneLineEdit->setText(phone); }
void CustomerDialog::setAge(int age) { ui->ageLineEdit->setText(QString::number(age)); }
void CustomerDialog::setName(const QString& name) { ui->nameLineEdit->setText(name); }

// getters for ui elements
QString CustomerDialog::getPersonNr() const { return ui->personalNumberLineEdit->text(); }
QString CustomerDialog::getEmail() const { return ui->emailLineEdit->text(); }
QString CustomerDialog::getPhone() const { return ui->phoneLineEdit->text(); }
int CustomerDialog::getAge() const { return ui->ageLineEdit->text().toInt(); }
QString CustomerDialog::getName() const { return ui->nameLineEdit->text(); }
QLineEdit* CustomerDialog::getPersonNrLineEdit() const { return ui->personalNumberLineEdit; }