#ifndef HELLHUB_CARDIALOG_H
#define HELLHUB_CARDIALOG_H

#include "../CarManager.h"

#include <QDialog>
#include <QLineEdit>

namespace Ui {
    class CarDialog;
}

class CarDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CarDialog(QWidget *parent = nullptr);
    ~CarDialog();

    // Setters for UI elements
    void setRegNr(const QString &RegNr);
    void setMake(const QString &make);
    void setModel(const QString &model);
    void setColor(const QString &color);
    void setCarType(const QString& carType);
    void setFuelType(const QString& fuelType);
    void setYear(int year);
    void setPrice(int price);
    void setKmDriven(int kmDriven);
    void setSeats(int seats);
    void setAvailable(bool available);

    // Getters for UI elements
    QString getRegNr() const;
    QString getMake() const;
    QString getModel() const;
    QString getColor() const;
    QString getCarType() const;
    QString getFuelType() const;
    int getYear() const;
    int getPrice() const;
    int getKmDriven() const;
    int getSeats() const;
    bool getAvailable() const;

    // Getter for regNr edit field
    QLineEdit* getRegNrLineEdit() const;

    // convert to close edit dialog
    void convertToCloseDialog();

    // populate fields with car data
    void populateFields(Car &selectedCar);

private:
    Ui::CarDialog *ui;
};

#endif //HELLHUB_CARDIALOG_H
