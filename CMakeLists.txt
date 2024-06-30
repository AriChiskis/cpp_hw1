cmake_minimum_required(VERSION 3.27)
project(cpp_hw1)

set(CMAKE_CXX_STANDARD 20)

add_executable(myrobot main.cpp
        House/IHouse.hpp
        House/House.hpp
        House/House.cpp
        Cleaner/ICleaner.hpp
        Cleaner/VaccumCleaner/VacuumCleaner.hpp
        Cleaner/VaccumCleaner/VacuumCleaner.cpp
        Sensor/HouseSensor/HouseSensor.cpp
        Sensor/HouseSensor/WallSensor/WallSensor.cpp
        Sensor/HouseSensor/DirtSensor/DirtSensor.hpp
        Sensor/HouseSensor/DirtSensor/DirtSensor.cpp
        Sensor/BaterrySensor/BatterySensor.hpp
        Sensor/BaterrySensor/BatterySensor.cpp
        DynamicMap/DynamicMap.cpp
        CleaningAlgorithm/CleaningAlgorithm.hpp
        CleaningAlgorithm/CleaningAlgorithm.cpp)
