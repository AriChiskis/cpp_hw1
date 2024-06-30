#ifndef IHOUSE_HPP
#define IHOUSE_HPP

#include "../IEnvironment.hpp"

class IHouse : public IEnvironment {
public:
    virtual int getDirtLevel(int x, int y) const = 0;
    virtual bool isWall(int x, int y) const = 0;
    virtual ~IHouse() {}
};

#endif // IHOUSE_HPP
