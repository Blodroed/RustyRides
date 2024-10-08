//
// Created by Albert on 17.04.2024.
//

#ifndef HELLHUB_CAR_H
#define HELLHUB_CAR_H

#include <QString>


class Car {
public:
    // Constructor
    Car();
    explicit Car(const QString &regNr, const QString& make, const QString &model, const QString &color, const QString &carType,
                 const QString &fuelType, int year, int price, int kmDriven,
                 int seats, bool available);

    // Destructor
    virtual ~Car();

    // Setters for private members
    void setRegNr(const QString &RegNr);
    void setMake(const QString &make);
    void setModel(const QString &model);
    void setColor(const QString &color);
    void setCarType(const QString &carType);
    void setFuelType(const QString &fuelType);
    void setYear(int year);
    void setPrice(int price);
    void setKmDriven(int kmDriven);
    void setSeats(int seats);
    void setAvailable(bool available);

    // Getters for each private member
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
    
private:
    QString RegNr;
    QString color;
    QString make;
    QString model;
    QString carType;
    QString fuelType;
    int year;
    int price;
    int kmDriven;
    int seats;
    bool available;
};




#endif //HELLHUB_CAR_H
