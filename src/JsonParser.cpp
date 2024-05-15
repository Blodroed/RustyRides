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
#include <QString>

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
                carJson["carType"].GetString(), carJson["fuelType"].GetString(), carJson["year"].GetInt(),
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
 * The car is added to the end of the cars array in the JSON file.
 * The car's attributes are used to create a new JSON object, which is then added to the cars array.
 *
 * @param car A reference to a Car object to be exported to the JSON file.
 */
void JsonParser::exportSingleCarToJson(const Car &car) {
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
    carJson.AddMember("fuelType", rapidjson::Value(car.getFuelType().c_str(), allocator).Move(), allocator);
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

/**
 * @brief Edits a single car in the JSON file.
 *
 * This function edits a single car in the JSON file.
 * The car is identified by the registration number.
 *
 * @param car A reference to a Car object to be edited in the JSON file.
 */
 void JsonParser::editSingleCarToJson(const Car &car) {
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

    // creating an allocator for the JSON object
    auto &allocator = doc.GetAllocator();

    for (Value::ValueIterator itr = doc["cars"].Begin(); itr != doc["cars"].End(); ++itr) {
        Value &carJson = *itr;      // dereference the iterator to get the car object
        if (carJson["regNr"].GetString() == targetRegNr) {
            // Update car's attributes other than the registration number
            carJson["color"].SetString(car.getColor().c_str(), allocator);
            carJson["model"].SetString(car.getModel().c_str(), allocator);
            carJson["carType"].SetString(car.getCarType().c_str(), allocator);
            carJson["fuelType"].SetString(car.getFuelType().c_str(), allocator);
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

 void JsonParser::deleteSingleCarFromJson(const Car *car) {
    // much needed variables
    std::string targetRegNr = car->getRegNr();   // need this for some reason to work with comparisons

    // same procedure as last year ms SOfie?
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }
    // same procedure as every year, James
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    /*
     * we should also check if the car is available before deleting it
     */

     // Iterate over the cars array
     for (Value::ValueIterator itr = doc["cars"].Begin(); itr != doc["cars"].End();) {
         Value &carJson = *itr;
         if (carJson["regNr"].GetString() == targetRegNr) {
             // If the registration number matches, erase this element
             itr = doc["cars"].Erase(itr);
             // for some dumb reason the program crashed when we breaked out of the loop before
             // it had gone through all the cars
         } else {
             ++itr;
         }
     }

    // writing to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
 }
/** @} */ // end of CarFunctions group

/**
 * @defgroup CustomerFunctions
 * @brief Customer-related JSON parsing functions
 *
 * This group contains all the functions related to parsing JSON data for customers.
 * @{
 */

void JsonParser::importCustomersFromJson(std::vector<Customer> &customers) {
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
    const auto &customersJson = doc["customers"];

    // clear the vector before adding new customers
    // this is to avoid duplicates. Database is considered to be the truth
    customers.clear();

    // iterating through the cars array and adding it to the vector
    for (const auto &customerJson : customersJson.GetArray()) {
        if (!customerJson.IsObject()) {
            std::cout << "Error: customer is not an object in the JSON document" << std::endl;
            continue;
        }

        QString personNummer = QString::fromStdString(customerJson["personNummer"].GetString());
        QString name = QString::fromStdString(customerJson["name"].GetString());
        QString phoneNumber = QString::fromStdString(customerJson["phoneNumber"].GetString());
        QString email = QString::fromStdString(customerJson["email"].GetString());
        int age = customerJson["age"].GetInt();

        std::vector<QString> cars;
        if (customerJson.HasMember("cars") && customerJson["cars"].IsArray()) {
            for (const auto &carJson: customerJson["cars"].GetArray()) {
                cars.push_back(QString::fromStdString(carJson.GetString()));
            }
        }
        Customer customer(personNummer, email, phoneNumber, age, name, cars);
        customers.emplace_back(std::move(customer));
    }
}

/** @} */ // end of CustomerFunctions group