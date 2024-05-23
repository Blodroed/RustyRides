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

JsonParser::~JsonParser() = default;


void JsonParser::setFilepath(const std::string &newFilepath) {
    /* Set the filepath for the json file
     * the filepath is set upon construction of the class,
     * but with this function you can change it with the filepath in the argument
     */
    this->filepath = newFilepath;
}

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
        Car car(QString::fromStdString(carJson["regNr"].GetString()),
                QString::fromStdString(carJson["make"].GetString()),
                QString::fromStdString(carJson["model"].GetString()),
                QString::fromStdString(carJson["color"].GetString()),
                QString::fromStdString(carJson["carType"].GetString()),
                QString::fromStdString(carJson["fuelType"].GetString()),
                carJson["year"].GetInt(),
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

    carJson.AddMember("regNr", rapidjson::Value((car.getRegNr().toStdString().c_str()), allocator).Move(), allocator);
    carJson.AddMember("make", rapidjson::Value(car.getMake().toStdString().c_str(), allocator).Move(), allocator);
    carJson.AddMember("model", rapidjson::Value(car.getModel().toStdString().c_str(), allocator).Move(), allocator);
    carJson.AddMember("color", rapidjson::Value(car.getColor().toStdString().c_str(), allocator).Move(), allocator);
    carJson.AddMember("carType", rapidjson::Value(car.getCarType().toStdString().c_str(), allocator).Move(), allocator);
    carJson.AddMember("fuelType", rapidjson::Value(car.getFuelType().toStdString().c_str(), allocator).Move(), allocator);
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
    std::string targetRegNr = car.getRegNr().toStdString();   // need this for some reason to work with comparisons
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
            carJson["make"].SetString(car.getMake().toStdString().c_str(), allocator);
            carJson["model"].SetString(car.getModel().toStdString().c_str(), allocator);
            carJson["color"].SetString(car.getColor().toStdString().c_str(), allocator);
            carJson["carType"].SetString(car.getCarType().toStdString().c_str(), allocator);
            carJson["fuelType"].SetString(car.getFuelType().toStdString().c_str(), allocator);
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

 void JsonParser::deleteSingleCarFromJson(const Car &car) {
    // much needed variables
    std::string targetRegNr = car.getRegNr().toStdString();   // need this for some reason to work with comparisons

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
     * TODO: we should also check if the car is available before deleting it
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
            std::cout << "Error: skipping the entry, not an object" << std::endl;
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

void JsonParser::exportSingleCustomerToJson(const Customer &customer) {
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
    auto &customersJson = doc["customers"];

    // creating a new JSON object for the car
    rapidjson::Value customerJson(rapidjson::kObjectType);
    auto &allocator = doc.GetAllocator();

    customerJson.AddMember("personNummer", rapidjson::Value(customer.getPersonNr().toStdString().c_str(), allocator).Move(), allocator);
    customerJson.AddMember("email", rapidjson::Value(customer.getEmail().toStdString().c_str(), allocator).Move(), allocator);
    customerJson.AddMember("phoneNumber", rapidjson::Value(customer.getPhone().toStdString().c_str(), allocator).Move(), allocator);
    customerJson.AddMember("age", customer.getAge(), allocator);
    customerJson.AddMember("name", rapidjson::Value(customer.getName().toStdString().c_str(), allocator).Move(), allocator);

    // adding the cars array to the customer object
    customerJson.AddMember("cars", rapidjson::Value(rapidjson::kArrayType), allocator);
    for (const auto &car : customer.getAssignedCarsRegNr()) {
        customerJson["cars"].PushBack(rapidjson::Value(car.toStdString().c_str(), allocator).Move(), allocator);
    }

    doc["customers"].PushBack(customerJson, allocator);

    // writing the JSON object to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

void JsonParser::editSingleCustomerToJson(const Customer &customer) {
    // much needed variables
    std::string targetPersonNr = customer.getPersonNr().toStdString();   // need this for some reason to work with comparisons
    std::ifstream file(filepath);               // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }

    // converting the ifstream to IStreamWrapper
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    // get allocator
    auto &allocator = doc.GetAllocator();

    for (Value::ValueIterator itr = doc["customers"].Begin(); itr != doc["customers"].End(); ++itr) {
        Value &customerJson = *itr;      // dereference the iterator to get the customer object
        if (customerJson["personNummer"].GetString() == targetPersonNr) {
            // Update customer's attributes other than the personnummer
            customerJson["email"].SetString(customer.getEmail().toStdString().c_str(), allocator);
            customerJson["phoneNumber"].SetString(customer.getPhone().toStdString().c_str(), allocator);
            customerJson["age"].SetInt(customer.getAge());
            customerJson["name"].SetString(customer.getName().toStdString().c_str(), allocator);
            // update the cars array
            customerJson["cars"].Clear();
            for (const auto &car: customer.getAssignedCarsRegNr()) {
                customerJson["cars"].PushBack(rapidjson::Value(car.toStdString().c_str(), allocator).Move(), allocator);
            }
            break; // Once found and updated, exit the loop
        }
    }

    // writing the JSON object to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

void JsonParser::deleteSingleCustomerFromJson(const Customer &customer) {
    // target personnummer
    std::string targetPersonNr = customer.getPersonNr().toStdString();

    // same procedure as last year ms SOfie?
    std::ifstream
    file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }
    // same procedure as every year, James
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    // Iterate over the customers array
    for (Value::ValueIterator itr = doc["customers"].Begin(); itr != doc["customers"].End();) {
        Value &customerJson = *itr;
        if (customerJson["personNummer"].GetString() == targetPersonNr) {
            // If the personnummer matches, erase this element
            itr = doc["customers"].Erase(itr);
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
/** @} */ // end of CustomerFunctions group

/**
 * @defgroup LeaseFunctions
 * @brief Lease-related JSON parsing functions
 *
 * This group contains all the functions related to parsing JSON data for leases.
 * @{
 */

void JsonParser::importLeasesFromJson(std::vector<Lease> &leases) {
    std::ifstream file(filepath); // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    // accessing the leases array directly
    const auto &leasesJson = doc["leases"];

    leases.clear();

    for (const auto &leaseJson : leasesJson.GetArray()) {
        if (!leaseJson.IsObject()) {
            std::cout << "Error: skipping the entry, not an object" << std::endl;
            continue;
        }

        int leaseId = leaseJson["leaseId"].GetInt();
        QString regNr = QString::fromStdString(leaseJson["regNr"].GetString());
        QString personNummer = QString::fromStdString(leaseJson["customerId"].GetString());
        QString startDate = QString::fromStdString(leaseJson["startDate"].GetString());
        int daysOfLease = leaseJson["daysOfLease"].GetInt();
        int negotiatedPrice = leaseJson["negotiatedPrice"].GetInt();
        int totalPrice = leaseJson["totalPrice"].GetInt();
        bool openOrClosed = leaseJson["open"].GetBool();

        // creation and adding of lease object to vector
        Lease lease(leaseId, regNr, personNummer, startDate, daysOfLease, negotiatedPrice, totalPrice, openOrClosed);
        leases.emplace_back(std::move(lease));
    }
}

void JsonParser::exportLeasesToJson(const std::vector<Lease> &leases) {}

void JsonParser::exportSingleLeaseToJson(const Lease &lease) {
    std::ifstream file(filepath); // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }

    // converting the ifstream to IStreamWrapper
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    // accessing the leases array directly
    auto &leasesJson = doc["leases"];

    rapidjson::Value leaseJson(rapidjson::kObjectType);
    auto &allocator = doc.GetAllocator();

    leaseJson.AddMember("leaseId", lease.getleaseId(), allocator);
    leaseJson.AddMember("regNr", rapidjson::Value(lease.getRegNr().toStdString().c_str(), allocator).Move(), allocator);
    leaseJson.AddMember("customerId", rapidjson::Value(lease.getPersonNr().toStdString().c_str(), allocator).Move(), allocator);
    leaseJson.AddMember("startDate", rapidjson::Value(lease.getStartDate().toStdString().c_str(), allocator).Move(), allocator);
    leaseJson.AddMember("daysOfLease", lease.getDaysOfLease(), allocator);
    leaseJson.AddMember("negotiatedPrice", lease.getNegotiatedPrice(), allocator);
    leaseJson.AddMember("totalPrice", lease.getTotalPrice(), allocator);
    leaseJson.AddMember("open", lease.isOpenOrClosed(), allocator);

    doc["leases"].PushBack(leaseJson, allocator);

    // writing the JSON object to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

void JsonParser::editSingleLeaseToJson(const Lease &lease) {
    // much needed variables
    int targetLeaseId = lease.getleaseId();   // need this for some reason to work with comparisons
    std::ifstream file(filepath);             // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }

    // converting the ifstream to IStreamWrapper
    IStreamWrapper isw(file);
    Document doc;
    doc.ParseStream(isw);
    file.close();

    // get allocator
    auto &allocator = doc.GetAllocator();

    for (Value::ValueIterator itr = doc["leases"].Begin(); itr != doc["leases"].End(); ++itr) {
        Value &leaseJson = *itr;      // dereference the iterator to get the lease object
        if (leaseJson["leaseId"].GetInt() == targetLeaseId) {
            // Update lease's attributes other than the leaseId
            leaseJson["regNr"].SetString(lease.getRegNr().toStdString().c_str(), allocator);
            leaseJson["customerId"].SetString(lease.getPersonNr().toStdString().c_str(), allocator);
            leaseJson["startDate"].SetString(lease.getStartDate().toStdString().c_str(), allocator);
            leaseJson["daysOfLease"].SetInt(lease.getDaysOfLease());
            leaseJson["negotiatedPrice"].SetInt(lease.getNegotiatedPrice());
            leaseJson["totalPrice"].SetInt(lease.getTotalPrice());
            leaseJson["open"].SetBool(lease.isOpenOrClosed());
            break; // Once found and updated, exit the loop
        }
    }

    // writing the JSON object to the file
    std::ofstream ofstream(filepath);
    rapidjson::OStreamWrapper osw(ofstream);
    rapidjson::PrettyWriter<rapidjson::OStreamWrapper> writer(osw);
    doc.Accept(writer);
}

void JsonParser::deleteSingleLeaseFromJson(const Lease &lease) {
    // target leaseId
    int targetLeaseId = lease.getleaseId();

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

    // Iterate over the leases array
    for (Value::ValueIterator itr = doc["leases"].Begin(); itr != doc["leases"].End();) {
        Value &leaseJson = *itr;
        if (leaseJson["leaseId"].GetInt() == targetLeaseId) {
            // If the leaseId matches, erase this element
            itr = doc["leases"].Erase(itr);
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

/** @} */ // end of LeaseFunctions group

/**
 * @defgroup ImportExportFunctions
 * @brief Importing and exporting the entire database
 *
 * This group contains all the functions related to importing and exporting the entire database.
 * @{
 */

void JsonParser::fullBackup(const std::string &backupPath) {
    // open the source database
    std::ifstream srcFile(filepath, std::ios::binary);

    // check if the file opened successfully
    if (!srcFile.is_open()) {
        std::cout << "Error: Failed to open the source file" << std::endl;
        return;
    }

    // open the destination file
    std::ofstream destFile(backupPath, std::ios::binary);

    // check if the file opened successfully
    if (!destFile.is_open()) {
        std::cout << "Error: Failed to open the destination file" << std::endl;
        return;
    }

    // copy the contents of the source file to the destination file
    destFile << srcFile.rdbuf();
}

/** @} */ // end of ImportExportFunctions group