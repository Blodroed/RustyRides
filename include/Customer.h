//
// Created by Marcu on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMER_H
#define HELLHUB_CUSTOMER_H

#include <QDialog>
#include <QString>
#include <vector>

namespace Ui {
    class Customer;
}

class Customer : public QDialog
{
    Q_OBJECT

public:
    explicit Customer(QWidget *parent = nullptr);
    Customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name);

    // Move constructor and assignment operator
    Customer(Customer&& other) noexcept;
    Customer& operator=(Customer&& other) noexcept;

    Customer(const Customer& other) = delete;
    Customer& operator=(const Customer& other) = delete;

    ~Customer();

    void setPersonNr(const QString &personNr);
    void setEmail(const QString &email);
    void setPhone(const QString &phone);
    void setAge(int age);
    void setName(const QString &name);

    QString getPersonNr() const;
    QString getEmail() const;
    QString getPhone() const;
    int getAge() const;
    QString getName() const;

private:
    Ui::Customer *ui;
    QString personNr;
    QString email;
    QString phone;
    int age;
    QString name;
};

#endif //HELLHUB_CUSTOMER_H
