cmake_minimum_required(VERSION 3.28)
project(HellHub)

set(CMAKE_CXX_STANDARD 14) # has to be 14 for qt cmake to work

# Add RapidJSON headers directory to the include path
include_directories(libs/rapidjson)

# source files
add_executable(HellHub
        main.cpp
        include/Car.h
        src/Car.cpp
        include/CarManager.h
        src/CarManager.cpp
        test/carAdderTest.cpp
        include/JsonParser.h
        src/JsonParser.cpp
        test/carAddToJsonTest.cpp)
