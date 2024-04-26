//
// Created by Albert on 26.04.2024.
//

#ifndef HELLHUB_JSONPARSER_H
#define HELLHUB_JSONPARSER_H

#include "Car.h"

#include <vector>
#include <fstream>


class JsonParser {
public:
    // default constructor with filepath to database.json
    JsonParser(){
        filepath = "../database/database.json";
    };
    ~JsonParser();

    // constructor with custom filepath
    // remember to close the file after using it
    explicit JsonParser(const std::string &filepath);

    // set filepath
    void setFilepath(const std::string &filepath);

    // functions for importing and exporting to json
    void importCarJson(const std::vector<Car> &cars);
    void exportCarJson(const std::vector<Car> &cars);

private:
    std::string filepath;
};


#endif //HELLHUB_JSONPARSER_H
