#ifndef HOUSE_HPP
#define HOUSE_HPP

#include "IHouse.hpp"
#include <vector>
#include <utility> // for std::pair
#include <stdexcept>

class HouseOutOfBoundsException : public std::out_of_range {
public:
    HouseOutOfBoundsException(const std::string& message) : std::out_of_range(message) {}
};

class House : public IHouse {
private:
    std::vector<std::vector<char>> grid;
    std::pair<int, int> dockingStation;  // Only one docking station
    std::pair<int, int> position;

    void checkBounds(int x, int y) const;

public:
    House(const std::string& filename);
    virtual ~House() {}

    // Implementation of IHouse interface
    int getDirtLevel(int x, int y) const override;
    bool isWall(int x, int y) const override;
    void print(bool printDimensions = true) const;
    void decrementDirt(int x, int y);
    std::pair<int, int> getDockingStation();  // Declare this method
    void printCoordinate(int x, int y) const;
    void printAllCoordinates() const;
    bool isHouseClean() const; // for the report at the end :)
    int calculateTotalDirt() const;
};


#endif // HOUSE_HPP
