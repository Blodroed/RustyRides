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

/**
 * @class customer
 * @brief Represents a customer in the system.
 *
 * This class provides a representation of a customer, including personal details
 * and methods for manipulating these details. It extends QDialog to facilitate
 * UI interaction in a Qt application.
 */
class customer : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for creating a new customer instance with parent widget.
     * @param parent The parent widget of this dialog, defaults to nullptr.
     */
    explicit customer(QWidget *parent = nullptr);

    /**
     * @brief Constructor with detailed initialization.
     * @param personNr Customer's personal number.
     * @param email Customer's email address.
     * @param phone Customer's phone number.
     * @param age Customer's age.
     * @param name Customer's full name.
     */
    customer(const QString &personNr, const QString &email, const QString &phone, int age, const QString &name);

    /**
     * @brief Destructor
     */
    ~customer();

    /**
     * @brief Move constructor.
     * @param other Another customer object to move data from.
     */
    customer(customer&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other Another customer object to assign from.
     * @return A reference to this instance.
     */
    customer& operator=(customer&& other) noexcept;

    // Setters
    /**
     * @brief Sets the customer's personal number.
     * @param personNr New personal number to set.
     */
    void setPersonNr(const QString &personNr);

    /**
     * @brief Sets the customer's email address.
     * @param email New email address to set.
     */
    void setEmail(const QString &email);

    /**
     * @brief Sets the customer's phone number.
     * @param phone New phone number to set.
     */
    void setPhone(const QString &phone);

    /**
     * @brief Sets the customer's age.
     * @param age New age to set.
     */
    void setAge(int age);

    /**
     * @brief Sets the customer's name.
     * @param name New name to set.
     */
    void setName(const QString &name);

    // Getters
    /**
     * @brief Gets the customer's personal number.
     * @return Customer's personal number as a QString.
     */
    QString getPersonNr() const;

    /**
     * @brief Gets the customer's email address.
     * @return Customer's email address as a QString.
     */
    QString getEmail() const;

    /**
     * @brief Gets the customer's phone number.
     * @return Customer's phone number as a QString.
     */
    QString getPhone() const;

    /**
     * @brief Gets the customer's age.
     * @return Customer's age as an int.
     */
    int getAge() const;

    /**
     * @brief Gets the customer's name.
     * @return Customer's name as a QString.
     */
    QString getName() const;

private:
    Ui::customer *ui; ///< Pointer to the user interface setup for this dialog.
    QString personNr; ///< Customer's personal number.
    QString email; ///< Customer's email address.
    QString phone; ///< Customer's phone number.
    int age; ///< Customer's age.
    QString name; ///< Customer's full name.
};

#endif //HELLHUB_CUSTOMER_H
