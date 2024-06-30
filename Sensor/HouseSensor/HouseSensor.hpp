#ifndef HOUSESENSOR_HPP
#define HOUSESENSOR_HPP

#include "../ISensor.hpp"
#include "../../House/House.hpp"
#include <utility>  // for std::pair
#include <iostream>

class HouseSensor : public ISensor {
protected:
    House& house;
    std::pair<int, int> position; // Current position of the vacuum cleaner in the house

public:
    HouseSensor(House& house, std::pair<int, int> startPos);

    // Ensure this is declared const if it doesn't modify the object
    std::pair<int, int> getPosition() const;

    void updatePosition(int x, int y);
    void print(bool printDimensions = true) const;
};

#endif // HOUSESENSOR_HPP
