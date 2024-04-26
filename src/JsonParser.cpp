//
// Created by Albert on 26.04.2024.
//

#include "../include/JsonParser.h"

#include <iostream>

JsonParser::JsonParser(const std::string &filepath) {
    this->filepath = filepath;
};

void JsonParser::setFilepath(const std::string &filepath) {
    this->filepath = filepath;
};

void JsonParser::importCarJson(const std::vector<Car> &cars) {
    std::ifstream file(filepath); // filepath should be set on construction of class
    if (!file.is_open()) {
        std::cerr << "Error: File not found or failed to open" << std::endl;
        return;
    }

}