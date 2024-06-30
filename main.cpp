#include "House/House.hpp"
#include "Cleaner/VaccumCleaner/VacuumCleaner.hpp"
#include "Sensor/HouseSensor/DirtSensor/DirtSensor.hpp"
#include "Sensor/HouseSensor/WallSensor/WallSensor.hpp"
#include "Sensor/BaterrySensor/BatterySensor.hpp"
#include "CleaningAlgorithm/CleaningAlgorithm.hpp"
#include <fstream>
#include <sstream>

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
      std::string baseName = std::filesystem::path(filename).stem().string(); 
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
        std::string resultFileName = "Output/result_" + baseName + ".txt";
        cleaningAlgorithm.writeOutputFile(resultFileName,totalDirt,result);


    } catch (const std::exception& e) {
        std::cerr << "Error during setup or execution: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}
