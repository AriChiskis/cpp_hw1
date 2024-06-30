#ifndef DIRTSENSOR_HPP
#define DIRTSENSOR_HPP

#include "../HouseSensor.hpp"

class DirtSensor : public HouseSensor {
public:
    DirtSensor(House& house, std::pair<int, int> startPos);

    // Method to check dirt level at the current position
    int checkDirtLevel() const;
    void decrementDirt();

};


#endif // DIRTSENSOR_HPP