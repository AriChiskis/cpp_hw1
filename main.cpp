#include "House/House.hpp"
#include "Cleaner/VaccumCleaner/VacuumCleaner.hpp"
#include "Sensor/HouseSensor/DirtSensor/DirtSensor.hpp"
#include "Sensor/HouseSensor/WallSensor/WallSensor.hpp"
#include "Sensor/BaterrySensor/BatterySensor.hpp"
#include "CleaningAlgorithm/CleaningAlgorithm.hpp"
#include <fstream>
#include <sstream>
int runSimulation(){
    // File name containing the house layout
    std::string filename = "/Users/arielchiskis/Documents/cpp/Inputs/house_layout.txt";

    try {
        House house(filename);
        std::cout << "Calculating Totaldirt at start: " << house.calculateTotalDirt() << std::endl;
        DirtSensor dirtSensor(house,house.getDockingStation());
        WallSensor wallSensor(house,house.getDockingStation());
        BatterySensor batterySensor(100); // Assume a full battery capacity of 100 units
        VacuumCleaner vacuum(&batterySensor, &wallSensor, &dirtSensor, 20, 4); // Example maxSteps and batteryCapacity


        CleaningAlgorithm cleaningAlgorithm(vacuum);
        int result = cleaningAlgorithm.executeCleaningSession();
        int totalDirt = house.calculateTotalDirt();
        std::cout<< "saving report " << std::endl;
        cleaningAlgorithm.writeOutputFile("result.txt",totalDirt,result);


    } catch (const std::exception& e) {
        std::cerr << "Error during simulation: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}

void loadVacuumSettings(const std::string& filename, int& maxBattery, int& maxMissionSteps) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open configuration file: " + filename);
    }
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string key;
        int value;
        if (getline(iss, key, ':') && iss >> value) {
            if (key == "Max Battery") {
                maxBattery = value;
            } else if (key == "Max Mission Steps") {
                maxMissionSteps = value;
            }
        }
    }
    file.close();
}


int main(int argc, char* argv[]) {
    std::string filename = argv[1]; // Get the filename from the command line

    try {
        House house(filename);
        int maxBattery = 0;
        int maxMissionSteps = 0;
        loadVacuumSettings(filename, maxBattery, maxMissionSteps);
        BatterySensor batterySensor(maxBattery);
        DirtSensor dirtSensor(house,house.getDockingStation());
        WallSensor wallSensor(house,house.getDockingStation());
        VacuumCleaner vacuum(&batterySensor, &wallSensor, &dirtSensor, maxMissionSteps, maxBattery); // Example maxSteps and batteryCapacity
        // Continue with simulation setup

        CleaningAlgorithm cleaningAlgorithm(vacuum);
        int result = cleaningAlgorithm.executeCleaningSession();
        int totalDirt = house.calculateTotalDirt();
        std::cout<< "saving report " << std::endl;
        cleaningAlgorithm.writeOutputFile("result.txt",totalDirt,result);


    } catch (const std::exception& e) {
        std::cerr << "Error during setup or execution: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
