#include "CleaningAlgorithm.hpp"
#include <iostream>
#include <random> // For std::random_device and std::shuffle
#include <fstream>
#include <filesystem>
CleaningAlgorithm::CleaningAlgorithm(VacuumCleaner& vacuum)
        : vacuum(vacuum), map(), mapPosition(0, 0) {
    // Optionally set initial conditions on the map, such as marking the docking station
    map.set(mapPosition.first, mapPosition.second, 'D');  // Marking docking station
}


std::pair<int, int> directionToOffset(Direction dir) {
    switch (dir) {
        case NORTH: return {0, -1};
        case EAST:  return {1, 0};
        case SOUTH: return {0, 1};
        case WEST:  return {-1, 0};
        default:    return {0, 0};
    }
}

std::string directionToString(Direction dir) {
    switch (dir) {
        case NORTH: return "NORTH";
        case EAST:  return "EAST";
        case SOUTH: return "SOUTH";
        case WEST:  return "WEST";
        case STAY:  return "STAY";
        default:    return "UNKNOWN";
    }
}

void CleaningAlgorithm::moveAndProcess(Direction direction) {
    vacuum.move(direction);  // Move the vacuum cleaner in the specified direction

    // Update position based on the direction moved
    auto offset = directionToOffset(direction);
    mapPosition.first += offset.first;
    mapPosition.second += offset.second;

    // Check if the vacuum has returned to the docking station
    if (mapPosition.first == 0 && mapPosition.second == 0) {
        std::cout << "Vacuum has returned to the docking station." << std::endl;
    } else {
        // Get the current dirt level from the vacuum's sensor and update the map
        int dirtLevel = vacuum.checkDirtLevel();
        map.set(mapPosition.first, mapPosition.second, '0' + dirtLevel);
        std::cout << "Updated dirt level at (" << mapPosition.first << ", " << mapPosition.second
                  << ") to " << dirtLevel << "." << std::endl;
    }
}
std::vector<Direction> CleaningAlgorithm::updateMapAndFindOpenDirections() {
    std::vector<Direction> openDirections;
    std::vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};

    for (auto dir: directions) {
        auto offset = directionToOffset(dir);
        int newX = mapPosition.first + offset.first;
        int newY = mapPosition.second + offset.second;

        if (!vacuum.detectWall(dir)) {
            openDirections.push_back(dir);
        } else {
            map.set(newX, newY, 'W'); // Mark the wall in the map
        }
    }
    return openDirections;
}

void CleaningAlgorithm::navigate() {
    auto openDirections = updateMapAndFindOpenDirections();
    if (!openDirections.empty()) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(openDirections.begin(), openDirections.end(), g);
        Direction chosenDirection = openDirections.front();
        vacuum.move(chosenDirection);
        // Update position based on chosen direction
        auto offset = directionToOffset(chosenDirection);
        mapPosition.first += offset.first;
        mapPosition.second += offset.second;

        // pushing direction in to history
        history.push_back(chosenDirection);

        // Check if the vacuum has reached the docking station
        if (mapPosition.first == 0 && mapPosition.second == 0) {
            std::cout << "Vacuum has returned to the docking station." << std::endl;
        } else {
            // Get the current dirt level from the vacuum's sensor and update the map
            int dirtLevel = vacuum.checkDirtLevel();
            map.set(mapPosition.first, mapPosition.second, '0'+ dirtLevel);
            std::cout << "Updated dirt level at (" << mapPosition.first << ", " << mapPosition.second
                      << ") to " << dirtLevel << "." << std::endl;
        }
    } else {
        std::cout << "No available moves, considering backtracking or waiting." << std::endl;
    }
}

void CleaningAlgorithm::clean() {
    int dirtLevel = vacuum.checkDirtLevel();  // Get the current dirt level as an integer from the DirtSensor.

    if (dirtLevel > 0) {
        vacuum.clean();  // Instruct the vacuum cleaner to clean.
        dirtLevel = std::max(0, dirtLevel - 1);  // Decrease the dirt level by 1, ensuring it doesn't go below 0.
        map.set(mapPosition.first, mapPosition.second, '0' + dirtLevel);  // Update the map with the new integer dirt level.

        // Convert the integer dirt level to a character for display or further processing
        char dirtChar = '0' + dirtLevel;

        if (dirtLevel == 0) {
            std::cout << "Position (" << mapPosition.first << ", " << mapPosition.second << ") is now clean." << std::endl;
        } else {
            std::cout << "Dirt level at (" << mapPosition.first << ", " << mapPosition.second << ") reduced to " << dirtChar << "." << std::endl;
        }

        history.push_back(STAY);
    }
}


//void CleaningAlgorithm::executeCleaningSession() {
//    while (vacuum.getBatteryLevel() > 0) {
//        // Check if the vacuum is at the docking station
//        if (mapPosition.first == 0 && mapPosition.second == 0) {
//            std::cout << "Vacuum is at the docking station, deciding next move." << std::endl;
//            navigate();  // Make a decision to move even if at docking station
//        } else {
//            int dirtLevel = vacuum.checkDirtLevel();
//            if (dirtLevel > 0) {
//                std::cout << "Cleaning... Dirt level is " << dirtLevel << "." << std::endl;
//                clean();
//            } else {
//                std::cout << "No dirt found, moving to a new position." << std::endl;
//                navigate();
//            }
//        }
//
//        // Check if the vacuum needs to return to dock based on battery and distance
//        std::pair<std::vector<Direction>, int> pathToOrigin =
//                map.findPathToDock(mapPosition.first,mapPosition.second);
//
//        if (vacuum.getBatteryLevel() < pathToOrigin.second) {
//            std::cout << "Low battery relative to distance from dock, returning to dock." << std::endl;
//
//            vacuum.wallSensor->print();
//            break;
//        }
//    }
//}


int CleaningAlgorithm::executeCleaningSession() {
    while (vacuum.getBatteryLevel() > 0) {
        if (mapPosition.first == 0 && mapPosition.second == 0) {
            handleAtDockingStation();
        } else {
            cleanOrNavigate();
        }
        // Check if the vacuum needs to return to dock based on battery and distance
        std::pair<std::vector<Direction>, int> pathToOrigin = map.findPathToDock(mapPosition.first, mapPosition.second);
        int pathLength =  pathToOrigin.second;
        if (vacuum.getBatteryLevel() <= pathLength || vacuum.getStepsLeft() <= pathLength) {
            int result = returnToOrigin(pathToOrigin);
            if (result == 1) {
                std::cout << "We have returned to dock station." << std::endl;
                int thereAreNomoreSteps = rechargeFully();
                if (thereAreNomoreSteps == 1){
                    return 1; // finished with success
                    // else we continue in the loop
                }
            } else {
                std::cout << "Attempted to return to dock station but failed." << std::endl;
                std::cout << "we where suck in position (" << mapPosition.first << "," << mapPosition.second <<")"<< std::endl;

                return 0;
            }

        }
    }
    if (mapPosition.first == 0 && mapPosition.second == 0) {
        return 1;
    }
    else {
        return 0;
    }

}


void CleaningAlgorithm::handleAtDockingStation() {
    std::cout << "Vacuum is at the docking station, deciding next move." << std::endl;
    navigate();  // Decision making when at docking station
}

void CleaningAlgorithm::cleanOrNavigate() {
    int dirtLevel = vacuum.checkDirtLevel();
    if (dirtLevel > 0) {
        std::cout << "Cleaning... Dirt level is " << dirtLevel << "." << std::endl;
        clean();
    } else {
        std::cout << "No dirt found, moving to a new position." << std::endl;

        navigate();
    }
}





int CleaningAlgorithm::returnToOrigin(std::pair<std::vector<Direction>, int> pathToOrigin) {
    std::cout << "Initiating return to dock." << std::endl;
    //vacuum.wallSensor->print();  // Optionally printing sensor status

    // Iterate over the path to dock, moving step by step
    for (const auto& direction : pathToOrigin.first) {
        if (vacuum.getBatteryLevel() <= 0 || vacuum.getStepsLeft() <= 0) {
            std::cout << "Emergency stop: Battery or steps exhausted before reaching the dock." << std::endl;
            return 0;  // Indicate failure due to resource exhaustion
        }
        vacuum.move(direction);  // Perform the move in the specified direction
        updatePosition(direction);  // Update the position after moving
        history.push_back(direction);
    }

    // Check if the vacuum has successfully reached the docking station
    if (mapPosition.first == 0 && mapPosition.second == 0) {
        std::cout << "Vacuum successfully returned to docking station." << std::endl;
        return 1;  // Indicate successful return
    } else {
        std::cout << "Failed to return to docking station due to insufficient resources." << std::endl;
        return 0;  // Indicate failure to return
    }
}

void CleaningAlgorithm::updatePosition(Direction direction) {
    auto offset = directionToOffset(direction);
    mapPosition.first += offset.first;
    mapPosition.second += offset.second;
}
int CleaningAlgorithm::rechargeFully() {
    if (mapPosition.first == 0 && mapPosition.second == 0) { // Ensure vacuum is at docking station
        int stepsNeededForFullCharge = vacuum.howMuchToCharge();

        for (int i = 0; i < stepsNeededForFullCharge; ++i) {
            history.push_back(STAY);  // Add STAY to the history vector
        }
        std::cout << "Initiating recharge. Steps needed for full charge: " << stepsNeededForFullCharge << std::endl;
        vacuum.recharge(stepsNeededForFullCharge);
        int stepsLeft = vacuum.getStepsLeft();
        if (stepsLeft == 0) {
            std::cout << "function finished succesfully" << std::endl;
            return 1;
        }
        else{
            std::cout << "there are still stepsleft , lets clean" << std::endl;
            return 0;
        }

    }
    return 2;
}

//
//
//void CleaningAlgorithm::writeOutputFile(const std::string& filename, bool houseIsClean, int robotFinishedAtOrigin) {
//    try {
//        std::ofstream outFile(filename);
//        if (!outFile) {
//            throw std::runtime_error("Failed to open output file: " + filename);
//        }
//
//        outFile << "Steps History:" << std::endl;
//        for (const auto& step : history) {
//            outFile << directionToString(step) << " ";
//        }
//        outFile << std::endl << "Total Steps: " << history.size() << std::endl;
//        outFile << "Remaining Dirt: " << (houseIsClean ? "None" : "Present") << std::endl;
//        outFile << "Battery Status: " << (vacuum.getBatteryLevel() > 0 ? "Operational" : "Exhausted") << std::endl;
//        outFile << "Mission Status: " << (houseIsClean && robotFinishedAtOrigin ? "Succeeded" : "Failed") << std::endl;
//        outFile.close();
//    } catch (const std::exception& e) {
//        std::cerr << "Error writing to file: " << e.what() << std::endl;
//    }
//
//}

//
//void CleaningAlgorithm::writeOutputFile(const std::string& filename, bool houseIsClean, int robotFinishedAtOrigin) {
//    try {
//        std::ofstream outFile(filename);
//        if (!outFile) {
//            throw std::runtime_error("Failed to open output file: " + filename);
//        }
//
//        // Using filesystem to get the absolute path of the file
//        std::filesystem::path filePath = std::filesystem::absolute(filename);
//        std::cout << "Output file saved to: " << filePath << std::endl;  // Print the full path to the console
//
//        outFile << "Steps History:" << std::endl;
//        for (const auto& step : history) {
//            outFile << directionToString(step) << " ";
//        }
//        outFile << std::endl;
//        outFile << "Total Steps: " << history.size() << std::endl;
//        outFile << "Remaining Dirt: " << (houseIsClean ? "None" : "Present") << std::endl;
//        outFile << "Battery Status: " << (vacuum.getBatteryLevel() > 0 ? "Operational" : "Exhausted") << std::endl;
//        outFile << "Mission Status: " << (houseIsClean && robotFinishedAtOrigin ? "Succeeded" : "Failed") << std::endl;
//
//        outFile.close();  // Properly close the file
//    } catch (const std::exception& e) {
//        std::cerr << "Error writing to file: " << e.what() << std::endl;  // Catch and log any exceptions that occur during file operations
//    }
//}
//



void CleaningAlgorithm::writeOutputFile(const std::string& filename, int totalDirtLeft, int robotFinishedAtOrigin) {
    try {
        // Construct the full path to the output directory
        std::filesystem::path dirPath = std::filesystem::current_path() / "../Output";

        // Create the directory if it does not exist
        std::filesystem::create_directories(dirPath);  // Safely does nothing if the directory already exists

        // Append the filename to the directory path to get the full file path
        std::filesystem::path filePath = dirPath / filename;

        std::ofstream outFile(filePath);
        if (!outFile) {
            throw std::runtime_error("Failed to open output file: " + filePath.string());
        }

        std::cout << "Output file saved to: " << filePath << std::endl;  // Print the full path to the console

        // Write data to the file as before
        outFile << "Steps History:" << std::endl;
        for (const auto& step : history) {
            outFile << directionToString(step) << " ";
        }
        outFile << std::endl;
        outFile << "Total Steps: " << history.size() << std::endl;
        outFile << "Remaining Dirt: " << (totalDirtLeft) << std::endl;
        int batteryLevel = vacuum.getBatteryLevel();
        outFile << "Battery Status: " << (batteryLevel > 0 ? batteryLevel : 0  ) << std::endl;
        outFile << "Mission Status: " << ( (totalDirtLeft == 0) && robotFinishedAtOrigin ? "Succeeded" : "Failed") << std::endl;

        outFile.close();  // Properly close the file
    } catch (const std::exception& e) {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
    }
}
