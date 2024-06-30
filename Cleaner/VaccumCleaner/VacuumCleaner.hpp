#ifndef VACUUMCLEANER_HPP
#define VACUUMCLEANER_HPP

#include "../ICleaner.hpp"
#include "../../Sensor/ISensor.hpp"  // Ensure this path correctly points to the ISensor interface
#include "../../Sensor/BaterrySensor/BatterySensor.hpp"  // Include specific sensors
#include "../../Sensor/HouseSensor/WallSensor/WallSensor.hpp"
#include "../../Sensor/HouseSensor/DirtSensor/DirtSensor.hpp"
#include "../../Directions/Directions.hpp"
#include <iostream>
#include <vector>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <utility>
class VacuumCleaner : public ICleaner {
    private:
        BatterySensor* batterySensor;
        DirtSensor* dirtSensor;
        std::pair<int, int> dockingStation;
        std::pair<int, int> position;
        int stepsLeft; // Total operational steps left
        int maxBattery;  // Maximum number of steps allowed for the mission

        void updateSensors();

    public:
    WallSensor* wallSensor;
    VacuumCleaner(BatterySensor* battery, WallSensor* wall, DirtSensor* dirt, int maxSteps,int batteryCapacity);
        ~VacuumCleaner();

        void move(Direction dir);
        void clean() override;
        void recharge(int stepsAtDock);
        int howMuchToCharge();
        void goBackToOrigin();
        int getBatteryLevel() const;
        int getStepsLeft() ;
        bool detectWall(Direction direction) const;
        int checkDirtLevel() const;
    };

#endif // VACUUMCLEANER_HPP