#ifndef ISENSOR_HPP
#define ISENSOR_HPP

#include "../IEnvironment.hpp"
#include "../Directions/Directions.hpp"
#include <utility> // for std::pair

class ISensor : public IEnvironment {
public:


    virtual ~ISensor() {}
};

#endif // ISENSOR_HPP
