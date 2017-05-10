cmake_minimum_required(VERSION 3.5)
project(Project-CAL)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Project-CAL/src/Source.cpp Project-CAL/src/Client.cpp Project-CAL/src/Item.cpp Project-CAL/src/Purchase.cpp Project-CAL/src/Supermarket.cpp Project-CAL/src/Truck.cpp)
add_executable(Project-CAL ${SOURCE_FILES})