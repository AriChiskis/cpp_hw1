#include "VacuumCleaner.hpp"

VacuumCleaner::VacuumCleaner(BatterySensor* battery, WallSensor* wall, DirtSensor* dirt, int maxSt,int batteryCapacity)
        : batterySensor(battery), wallSensor(wall), dirtSensor(dirt), stepsLeft(maxSt), maxBattery(batteryCapacity) {
    position = wallSensor->getPosition(); // Initialize starting position
}

VacuumCleaner::~VacuumCleaner() {
}

void VacuumCleaner::move(Direction dir) {
    if (stepsLeft > 0 && batterySensor->getBatteryLevel() > 0 && !detectWall(dir)) {
        switch (dir) {
            case NORTH: position.second--; break;
            case EAST:  position.first++;  break;
            case SOUTH: position.second++; break;
            case WEST:  position.first--;  break;
            default: break; // it will never happened because i want put it there
        }

        updateSensors();
        stepsLeft--;
        batterySensor->decrementBattery(1);  // Assuming each move consumes 1 unit of battery
    }
}

void VacuumCleaner::updateSensors() {
    wallSensor->updatePosition(position.first, position.second);
    dirtSensor->updatePosition(position.first, position.second);
}

int VacuumCleaner::getStepsLeft() {
    return stepsLeft;
}
void VacuumCleaner::recharge(int stepsAtDock) {
    int rechargePerStep = maxBattery / 20;
    int newCharge = batterySensor->getBatteryLevel() + stepsAtDock * rechargePerStep;
    if (newCharge > maxBattery) {
        newCharge = maxBattery;  // Ensure battery does not exceed maximum
    }
    batterySensor->setBatteryLevel(newCharge);
    stepsLeft += -stepsAtDock; // Very important
}

int VacuumCleaner::howMuchToCharge() {
    int rechargePerStep = maxBattery / 20;
    int neededCharge = maxBattery - batterySensor->getBatteryLevel();
    int neededSteps = neededCharge / rechargePerStep;
    if (neededCharge % rechargePerStep != 0) { // Since you cannot have a fraction of a step, you calculate the steps as
        neededSteps++;  // Ensure we account for incomplete steps needed for full charge
    }

    if (neededSteps > stepsLeft) {
        neededSteps = stepsLeft;  // Limit the charging to available steps
    }

    return neededSteps;
}

int VacuumCleaner::getBatteryLevel() const {
    return batterySensor->getBatteryLevel();
}


bool VacuumCleaner::detectWall(Direction direction) const {
    return wallSensor->detectWall(direction);
}

int VacuumCleaner::checkDirtLevel() const {
    return dirtSensor->checkDirtLevel();
}

void VacuumCleaner::clean() {
    if (batterySensor->getBatteryLevel() > 0 && stepsLeft > 0) {
        int dirtLevel = dirtSensor->checkDirtLevel();
        if (dirtLevel > 0) {
            dirtSensor->decrementDirt();  // Assuming decrementDirt method reduces the dirt level by 1
            batterySensor->decrementBattery(1);  // Assume each cleaning action costs 1 unit of battery
            stepsLeft--;  // If cleaning counts as a step
            std::cout << "Cleaning performed at position (" << position.first << ", " << position.second
                      << "). Battery level now at " << batterySensor->getBatteryLevel()
                      << ", Steps left: " << stepsLeft << std::endl;
        } else {
            std::cout << "No cleaning needed at position (" << position.first << ", " << position.second << ")." << std::endl;
        }
    } else {
        std::cout << "Cannot clean, either out of battery or steps." << std::endl;
    }
}

void VacuumCleaner::goBackToOrigin() {
    // Set the vacuum's position to the docking station
    position.first = dockingStation.first;
    position.second = dockingStation.second;
    updateSensors();
}

