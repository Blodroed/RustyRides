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
using namespace rapidjson;
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

/**
 * @defgroup CarFunctions
 * @brief Car-related JSON parsing functions
 *
 * This group contains all the functions related to parsing JSON data for cars.
 * @{
 */

/**
 * @brief Imports cars from a JSON file and adds them to the provided vector.
 *
 * This import method adds the cars to the vector given to the function.
 * The vector is cleared before adding new cars to avoid duplicates.
 * The database is considered to be the truth.
 *
 * @param cars A reference to a vector of Car objects. The vector is cleared before new cars are added.
 */
void JsonParser::importCarsFromJson(std::vector<Car> &cars) {
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

    // clear the vector before adding new cars
    // this is to avoid duplicates. Database is considered to be the truth
    cars.clear();

    // iterating through the cars array and adding it to the vector
    for (const auto &carJson : carsJson.GetArray()) {
        Car car(carJson["regNr"].GetString(), carJson["color"].GetString(), carJson["model"].GetString(),
                carJson["carType"].GetString(), carJson["year"].GetInt(),
                carJson["price"].GetInt(), carJson["kmDriven"].GetInt(),
                carJson["seats"].GetInt(), carJson["availability"].GetBool());
        cars.push_back(car);
    }
}
/**
 * @brief Exports the entire vector of cars to a JSON file.
 *
 * This function takes a reference to the vector of Car objects and exports them to the JSON file.
 * Note that cars already present in the JSON file will be skipped to avoid duplicates.
 *
 * @param cars A reference to a vector of Car objects to be exported to the JSON file.
 */
void JsonParser::exportCarsToJson(const std::vector<Car> &cars) {
    //TODO: er denne nødvendig? Med tanke på at vi har exportSingleCarToJson allerede legger til en bil i json fila
}
/**
 * @brief Exports a single car to a JSON file.
 *
 * This function exports a single car to the JSON file.
 * The car is identified by its registration number (regNr).
 * If a car with the same regNr is found in the JSON file, its attributes are updated.
 * If no matching car is found, no changes are made to the JSON file.
 *
 * @param car A reference to a Car object to be exported to the JSON file.
 * The car's attributes are used to update the matching car in the JSON file.
 */
void JsonParser::exportSingleCarToJson(const Car &car) {
    // much needed variables
    std::string targetRegNr = car.getRegNr();   // need this for some reason to work with comparisons
    std::ifstream file(filepath);               // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }

    // converting the ifstream to IStreamWrapper
    // then reads it into memory for JSON document object
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    // creating a new JSON object for the car
    auto &allocator = doc.GetAllocator();

    for (Value::ValueIterator itr = doc["cars"].Begin(); itr != doc["cars"].End(); ++itr) {
        Value& carJson = *itr;      // dereference the iterator to get the car object
        if (carJson["regNr"].GetString() == targetRegNr) {
            // Update car's attributes other than the registration number
            carJson["color"].SetString(car.getColor().c_str(), allocator);
            carJson["model"].SetString(car.getModel().c_str(), allocator);
            carJson["carType"].SetString(car.getCarType().c_str(), allocator);
            carJson["year"].SetInt(car.getYear());
            carJson["price"].SetInt(car.getPrice());
            carJson["kmDriven"].SetInt(car.getKmDriven());
            carJson["seats"].SetInt(car.getSeats());
            carJson["availability"].SetBool(car.getAvailable());
            break; // Once found and updated, exit the loop
        }
    }

    // writing the JSON object to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

/**
 * @brief Edits a single car in the JSON file.
 *
 * This function edits a single car in the JSON file.
 * The car is identified by the registration number.
 *
 * @param car A reference to a Car object to be edited in the JSON file.
 */
 void JsonParser::editSingleCarToJson(const Car &editCar) {
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
    auto &allocator = doc.GetAllocator();

    // iterating through the cars object to find and remove the existing car
    for (rapidjson::Value::MemberIterator itr = carsJson.MemberBegin(); itr != carsJson.MemberEnd(); ++itr) {
        if (itr->name.GetString() == editCar.getRegNr()) {
            carsJson.RemoveMember(itr);
            break;
        }
    }

    // creating a new JSON object for the edited car
    rapidjson::Value newCarJson(rapidjson::kObjectType);
    newCarJson.AddMember("regNr", rapidjson::Value(editCar.getRegNr().c_str(), allocator).Move(), allocator);
    newCarJson.AddMember("color", rapidjson::Value(editCar.getColor().c_str(), allocator).Move(), allocator);
    newCarJson.AddMember("model", rapidjson::Value(editCar.getModel().c_str(), allocator).Move(), allocator);
    newCarJson.AddMember("carType", rapidjson::Value(editCar.getCarType().c_str(), allocator).Move(), allocator);
    newCarJson.AddMember("year", editCar.getYear(), allocator);
    newCarJson.AddMember("price", editCar.getPrice(), allocator);
    newCarJson.AddMember("kmDriven", editCar.getKmDriven(), allocator);
    newCarJson.AddMember("seats", editCar.getSeats(), allocator);
    newCarJson.AddMember("availability", editCar.getAvailable(), allocator);

    // adding the edited car to the cars object
    carsJson.AddMember(rapidjson::Value(editCar.getRegNr().c_str(), allocator).Move(), newCarJson, allocator);

    // writing the JSON object to the file
    std::ofstream ofstream(filepath, std::ios::trunc);  // trunc to overwrite the file
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
 }

/** @} */ // end of CarFunctions group