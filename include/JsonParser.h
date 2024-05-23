#ifndef HELLHUB_JSONPARSER_H
#define HELLHUB_JSONPARSER_H

#include "Car.h"
#include "Customer.h"
#include "Lease.h"

#include <vector>
#include <fstream>

/**
 * @class JsonParser
 * @brief A class for parsing JSON data to the database.
 *
 * This class provides functions for importing and exporting data to and from a JSON file.
 * It also provides functions for editing entries in the JSON file.
 */

class JsonParser {
public:
    /**
     * @brief Default constructor with filepath to database.json
     */
    JsonParser(){
        this->filepath = "../database/database.json";
    };
    ~JsonParser();

    /**
     * @brief Constructor with custom filepath
     * @param filepath The path to the JSON file
     */
    explicit JsonParser(const std::string &filepath);

    /**
     * @brief Sets the filepath
     * @param filepath The path to the JSON file
     */
    void setFilepath(const std::string &filepath);

    // ===== Cars Functions ================================================
    /**
     * @defgroup CarFunctions
     * @brief Car-related JSON parsing functions
     *
     * This group contains all the functions related to parsing JSON data for cars.
     * @{
     */

    /**
     * @brief Imports cars from a JSON file and adds them to the provided vector.
     * @param cars A reference to a vector of Car objects. The vector is cleared before new cars are added.
     */
    void importCarsFromJson(std::vector<Car> &cars);
    /**
     * @brief Exports a single car to the JSON file.
     * @param car A reference to a Car object to be exported to the JSON file.
     */
    void exportSingleCarToJson(const Car &car);
    /**
     * @brief Edits a single car in the JSON file.
     * @param car A reference to a Car object to be edited in the JSON file.
     */
    void editSingleCarToJson(const Car &car);
    /**
     * @brief Deletes a single car from the JSON file.
     * @param car A reference to a Car object to be deleted from the JSON file.
     */
     void deleteSingleCarFromJson(const Car &car);

    /**@}*/

    // ===== Customers Functions ================================================
    void importCustomersFromJson(std::vector<Customer> &customers);
    void exportSingleCustomerToJson(const Customer &customer);
    void editSingleCustomerToJson(const Customer &customer);
    void deleteSingleCustomerFromJson(const Customer &customer);

    // ===== Leases Functions ================================================
    void importLeasesFromJson(std::vector<Lease> &leases);
    void exportSingleLeaseToJson(const Lease &lease);
    void editSingleLeaseToJson(const Lease &lease);
    void deleteSingleLeaseFromJson(const Lease &lease);

    // full backup and import
    void fullBackup(const std::string &backupPath);
    void fullImport(std::vector<Car> &cars, std::vector<Customer> &customers, std::vector<Lease> &leases,
                    const std::string &importPath);

private:
    std::string filepath;
};


#endif //HELLHUB_JSONPARSER_H
