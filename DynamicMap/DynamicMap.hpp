#ifndef DYNAMIC_MAP_HPP
#define DYNAMIC_MAP_HPP

#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
#include <string>
#include"../Directions/Directions.hpp"
class DynamicMap {
private:
    std::map<int, std::map<int, char>> grid;

public:
    DynamicMap();
    void set(int x, int y, char value);
    char get(int x, int y) const;
    std::pair<std::vector<Direction>, int> findPathToDock(int startX, int startY);
};

#endif // DYNAMIC_MAP_HPP
