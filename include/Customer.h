//
// Created by Marcu on 10.05.2024.
//

#ifndef HELLHUB_CUSTOMER_H
#define HELLHUB_CUSTOMER_H

#include <QDialog>
#include <QString>

namespace Ui {
    class customer;
}

class customer : public QDialog
{
    Q_OBJECT

public:
    explicit customer(QWidget *parent = nullptr);
    customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name);

    // Move constructor and assignment operator
    customer(customer&& other) noexcept;
    customer& operator=(customer&& other) noexcept;

    customer(const customer& other) = delete;
    customer& operator=(const customer& other) = delete;

    ~customer();

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
    Ui::customer *ui;
    QString personNr;
    QString email;
    QString phone;
    int age;
    QString name;
};

#endif //HELLHUB_CUSTOMER_H
