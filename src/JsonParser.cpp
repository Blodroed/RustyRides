//
// Created by Albert on 26.04.2024.
//

#include "../include/JsonParser.h"
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/istreamwrapper.h"

#include <iostream>

JsonParser::JsonParser(const std::string &filepath) {
    this->filepath = filepath;
};

JsonParser::~JsonParser() {
    /* Destructor for JsonParser
     * closes the file if it is open
     */
    // TODO: close file if open
};

void JsonParser::setFilepath(const std::string &filepath) {
    /* Set the filepath for the json file
     * the filepath is set upon construction of the class,
     * but with this function you can change it with the filepath in the argument
     */
    this->filepath = filepath;
};

void JsonParser::importCarJson(const std::vector<Car> &cars) {
    /* Importing cars from json file
     * this import method adds the cars to the vector given to the function
    */
    std::ifstream file(filepath); // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }

    // converting the ifstream to IStreamWrapper
    // then reads it into memory for JSON document object
    rapidjson::IStreamWrapper isw(file);
    rapidjson::Document doc;
    doc.ParseStream(isw);

    // accessing the cars array directly
    const auto &carsJson = doc["cars"];

    // iterating through the cars array and adding it to the vector
    for (const auto &carJson : carsJson.GetArray()) {
        std::string RegNr = carJson["RegNr"].GetString();

        // check if car already exist in the vector
        bool carExist = false;
        for (const auto &car : cars) {
            if (car.getRegNr() == RegNr) {
                carExist = true;
                break;
            }
        }

        int year = carJson["year"].GetInt();
        int price = carJson["price"].GetInt();
        int kmDriven = carJson["kmDriven"].GetInt();
        int seats = carJson["seats"].GetInt();

        cars.push_back(car);
    }

}