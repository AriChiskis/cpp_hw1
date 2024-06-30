#include "WallSensor.hpp"

WallSensor::WallSensor(House& house, std::pair<int, int> startPos)
        : HouseSensor(house, startPos) {}

bool WallSensor::detectWall(Direction direction) const {
    int x = position.first;
    int y = position.second;

    switch (direction) {
        case NORTH:
            return house.isWall(x, y - 1);
        case EAST:
            return house.isWall(x + 1, y);
        case SOUTH:
            return house.isWall(x, y + 1);
        case WEST:
            return house.isWall(x - 1, y);
        default:
            // Optionally handle invalid direction
            return false;
    }
}
std::map<Direction, bool> WallSensor::detectWalls() const {
    std::map<Direction, bool> walls;
    // Check each direction and update the map
    walls[NORTH] = house.isWall(position.first, position.second - 1);
    walls[EAST]  = house.isWall(position.first + 1, position.second);
    walls[SOUTH] = house.isWall(position.first, position.second + 1);
    walls[WEST]  = house.isWall(position.first - 1, position.second);

    return walls;
}
