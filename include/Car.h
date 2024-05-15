//
// Created by Alber on 17.04.2024.
//

#ifndef HELLHUB_CAR_H
#define HELLHUB_CAR_H

#include <string>

class Car {
public:
    // Constructor
    Car();
    explicit Car(const std::string &regNr, const std::string &color, const std::string &model, const std::string &carType,
                 const std::string &fuelType, int year, int price, int kmDriven, int seats, bool available);

    // Destructor
    virtual ~Car();

    // Setters for private members
    void setColor(std::string color);
    void setModel(std::string model);
    void setCarType(std::string carType);
    void setFuelType(std::string fuelType);
    void setYear(int year);
    void setPrice(int price);
    void setKmDriven(int kmDriven);
    void setSeats(int seats);
    void setAvailable(bool available);

    // Getters for each private member
    std::string getRegNr() const;
    std::string getColor() const;
    std::string getModel() const;
    std::string getCarType() const;
    std::string getFuelType() const;
    int getYear() const;
    int getPrice() const;
    int getKmDriven() const;
    int getSeats() const;
    bool getAvailable() const;
private:
    std::string RegNr;
    std::string color;
    std::string model;
    std::string carType;
    std::string fuelType;
    int year;
    int price;
    int kmDriven;
    int seats;
    bool available;
};


#endif //HELLHUB_CAR_H
