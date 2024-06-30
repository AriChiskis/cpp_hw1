#ifndef WALLSENSOR_HPP
#define WALLSENSOR_HPP

#include "../HouseSensor.hpp"  // Adjust the include path as necessary
#include "../../../Directions/Directions.hpp"
#include <utility>  // for std::pair
#include <map>

class WallSensor : public HouseSensor {
public:
    WallSensor(House& house, std::pair<int, int> startPos);

    // Unified method to detect walls in a given direction
    bool detectWall(Direction direction) const;
    std::map<Direction, bool> detectWalls() const;

};

#endif // WALLSENSOR_HPP
