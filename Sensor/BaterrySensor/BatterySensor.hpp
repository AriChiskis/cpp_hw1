#ifndef BATTERYSENSOR_HPP
#define BATTERYSENSOR_HPP
#include "../ISensor.hpp"

class BatterySensor  {
public:
    BatterySensor(int initialBatteryLevel);

    // Battery and steps getters
    int getBatteryLevel() const;
    int getStepsLeft() const;

    // Setters for battery and steps
    void setBatteryLevel(int newLevel);
    void setStepsLeft(int steps);

    // Decrement methods
    void decrementBattery(int amount);  // Decreases battery level
    void decrementSteps(int count);     // Decreases steps left

private:
    int batteryLevel;  // Current battery level

};

#endif // BATTERYSENSOR_HPP
