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
    explicit JsonParser(const std::string &filepath);

    // setters
    void setFilepath(const std::string &filepath);

    // ===== Cars Functions ================================================
    void importCarsFromJson(std::vector<Car> &cars);
    void exportSingleCarToJson(const Car &car);
    void editSingleCarToJson(const Car &car);
    void deleteSingleCarFromJson(const Car &car);

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