#ifndef HELLHUB_CUSTOMERDIALOG_H
#define HELLHUB_CUSTOMERDIALOG_H

#include "../CustomerManager.h"

#include <QDialog>
#include <QLineEdit>

namespace Ui {
    class CustomerDialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);
    ~CustomerDialog();

    // setters for ui elements
    void setPersonNr(const QString& personNr);
    void setEmail(const QString& email);
    void setPhone(const QString& phone);
    void setAge(int age);
    void setName(const QString& name);

    // getters for ui elements
    QString getPersonNr() const;
    QString getEmail() const;
    QString getPhone() const;
    int getAge() const;
    QString getName() const;

    // Get the edit field
    QLineEdit* getPersonNrLineEdit() const;

    // populate fields
    void populateFields(Customer &selectedCustomer);

private:
    Ui::CustomerDialog *ui;
    QLineEdit* personalNumberLineEdit;
};

#endif //HELLHUB_CUSTOMERDIALOG_H
