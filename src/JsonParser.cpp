//
// Created by Albert on 26.04.2024.
//

#include "../include/JsonParser.h"
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/prettywriter.h"
#include "../libs/rapidjson/istreamwrapper.h"
#include "../libs/rapidjson/ostreamwrapper.h"

#include <iostream>
#include <vector>

JsonParser::JsonParser(const std::string &filepath) {
    this->filepath = filepath;
}

JsonParser::~JsonParser() {
    /* Destructor for JsonParser
     * closes the file if it is open
     */
    // TODO: close file if open
};

void JsonParser::setFilepath(const std::string &newFilepath) {
    /* Set the filepath for the json file
     * the filepath is set upon construction of the class,
     * but with this function you can change it with the filepath in the argument
     */
    this->filepath = newFilepath;
};

void JsonParser::importCarFromJson(std::vector<Car> &cars) {
    /* Importing cars from json file
     * this import method adds the cars to the vector given to the function
     * WARNING: the vector is cleared before adding new cars
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
    file.close();

    // accessing the cars array directly
    const auto &carsJson = doc["cars"];

    cars.clear(); // clear the vector before adding new cars

    // iterating through the cars array and adding it to the vector
    for (const auto &carJson : carsJson.GetArray()) {
        Car car(carJson["regNr"].GetString(), carJson["color"].GetString(), carJson["model"].GetString(),
                carJson["carType"].GetString(), carJson["year"].GetInt(),
                carJson["price"].GetInt(), carJson["kmDriven"].GetInt(),
                carJson["seats"].GetInt(), carJson["availability"].GetBool());
        cars.push_back(car);
    }
}

void JsonParser::exportCarToJson(const std::vector<Car> &cars) {
    // TODO
}

void JsonParser::exportSingleCarToJson(const Car &car) {
    /* Exporting a single car to json file
     * this function exports a single car to the json file
     * the car is added to the end of the cars array in the json file
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
    file.close();

    // accessing the cars array directly
    auto &carsJson = doc["cars"];

    // creating a new JSON object for the car
    rapidjson::Value carJson(rapidjson::kObjectType);
    auto &allocator = doc.GetAllocator();

    carJson.AddMember("regNr", rapidjson::Value(car.getRegNr().c_str(), allocator).Move(), allocator);
    carJson.AddMember("color", rapidjson::Value(car.getColor().c_str(), allocator).Move(), allocator);
    carJson.AddMember("model", rapidjson::Value(car.getModel().c_str(), allocator).Move(), allocator);
    carJson.AddMember("carType", rapidjson::Value(car.getCarType().c_str(), allocator).Move(), allocator);
    carJson.AddMember("year", car.getYear(), allocator);
    carJson.AddMember("price", car.getPrice(), allocator);
    carJson.AddMember("kmDriven", car.getKmDriven(), allocator);
    carJson.AddMember("seats", car.getSeats(), allocator);
    carJson.AddMember("availability", car.getAvailable(), allocator);

    doc["cars"].PushBack(carJson, allocator);

    // writing the JSON object to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}