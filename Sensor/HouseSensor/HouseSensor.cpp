#include "HouseSensor.hpp"
#include <iostream>


HouseSensor::HouseSensor(House& house, std::pair<int, int> startPos)
        : house(house), position(startPos) {}

std::pair<int, int> HouseSensor::getPosition() const {
    return position;
}

void HouseSensor::updatePosition(int x, int y) {
    position = std::make_pair(x, y);
}

void HouseSensor::print(bool printDimensions) const {
    house.print(printDimensions);
}
