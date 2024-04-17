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
    explicit Car(std::string &color, std::string &model, std::string &carType, int year, int price, int kmDriven);

    // Destructor
    virtual ~Car();

    // Setters for private members
    void setColor(std::string color);
    void setPrice(int price);
    void setKmDriven(int kmDriven);
    void setAvailable(bool available);

    // Getters for each private member
    std::string getColor() const;
    std::string getModel() const;
    std::string getCarType() const;
    int getYear() const;
    int getPrice() const;
    int getKmDriven() const;
    bool getAvailable() const;
private:
    std::string color;
    std::string model;
    std::string carType;
    int year;
    int price;
    int kmDriven;
    bool available;
};


#endif //HELLHUB_CAR_H
