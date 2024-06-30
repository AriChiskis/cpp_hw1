#include "BatterySensor.hpp"

BatterySensor::BatterySensor(int initialBatteryLevel)
        :  batteryLevel(initialBatteryLevel) {}

int BatterySensor::getBatteryLevel() const {
    return batteryLevel;
}



void BatterySensor::setBatteryLevel(int newLevel) {
    batteryLevel = newLevel;
    if (batteryLevel < 0) {
        batteryLevel = 0;
    }
}



void BatterySensor::decrementBattery(int amount) {
    batteryLevel -= amount;
    if (batteryLevel < 0) {
        batteryLevel = 0;
    }
}

