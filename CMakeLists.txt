cmake_minimum_required(VERSION 3.28)
project(HellHub)

set(CMAKE_CXX_STANDARD 14)

add_executable(HellHub
        main.cpp
        include/Car.h
        src/Car.cpp
        include/CarManager.h
        src/CarManager.cpp)
