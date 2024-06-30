#include "DirtSensor.hpp"

DirtSensor::DirtSensor( House& house, std::pair<int, int> startPos)
        : HouseSensor(house, startPos) {}

int DirtSensor::checkDirtLevel() const {
    return house.getDirtLevel(position.first, position.second);
}
void DirtSensor::decrementDirt() {
    house.decrementDirt(position.first, position.second);
}