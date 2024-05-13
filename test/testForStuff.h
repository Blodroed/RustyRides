//
// Created by Alber on 09.05.2024.
//

#ifndef HELLHUB_TESTFORSTUFF_H
#define HELLHUB_TESTFORSTUFF_H

#include "../include/JsonParser.h"
#include "../include/CarManager.h"

class testForStuff {
public:
    static void carAddToJsonTest();
    static void carAdderTest();
    static void editCarTest(JsonParser &jsonParser);
    static void removeCarTest(JsonParser &jsonParser);
};


#endif //HELLHUB_TESTFORSTUFF_H
