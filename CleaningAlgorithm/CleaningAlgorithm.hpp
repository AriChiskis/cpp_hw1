#ifndef CLEANINGALGORITHM_HPP
#define CLEANINGALGORITHM_HPP

#include "../Cleaner/VaccumCleaner/VacuumCleaner.hpp"
#include "../DynamicMap/DynamicMap.hpp"
#include "../Directions/Directions.hpp"
#include <vector>

class CleaningAlgorithm {
private:
    VacuumCleaner &vacuum;
    DynamicMap map;
    std::pair<int, int> mapPosition; // Current position on the map


public:
    std::vector<Direction> history;

    CleaningAlgorithm(VacuumCleaner &vacuum);

    int executeCleaningSession(); // Manages the entire cleaning process
    void writeOutputFile(const std::string& filename, int totalDirtLeft , int robotFinishedAtOrigin);

private:
    void navigate(); // Navigate based on current sensor data
    void clean(); // Perform cleaning actions
    void moveAndProcess(Direction direction);

    std::vector<Direction> updateMapAndFindOpenDirections(); // Updates map with walls and finds open directions
    void updatePosition(Direction direction);

    void handleAtDockingStation();

    void cleanOrNavigate();

    int returnToOrigin(std::pair<std::vector<Direction>, int> pathToOrigin);

    int rechargeFully();



};
#endif // CLEANINGALGORITHM_HPP
