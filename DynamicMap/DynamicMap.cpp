#include "DynamicMap.hpp"
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <algorithm>


DynamicMap::DynamicMap() {
    grid[0][0] = 'D'; // Docking station at (0,0)
}

void DynamicMap::set(int x, int y, char value) {
    grid[y][x] = value;
}

char DynamicMap::get(int x, int y) const {
    auto it = grid.find(y);
    if (it != grid.end()) {
        auto jt = it->second.find(x);
        if (jt != it->second.end()) {
            return jt->second;
        }
    }
    return ' '; // Space indicates unvisited
}








std::pair<std::vector<Direction>, int> DynamicMap::findPathToDock(int startX, int startY) {
    // Base case where the start is already the docking station
    if (startX == 0 && startY == 0) {
        return {{}, 0};  // Empty path, zero length
    }

    std::queue<std::pair<int, int>> queue;
    std::map<std::pair<int, int>, std::pair<int, int>> cameFrom;
    std::map<std::pair<int, int>, Direction> path;

    queue.push({startX, startY});
    cameFrom[{startX, startY}] = {-1, -1};  // Mark starting point

    std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::vector<Direction> dirNames = {NORTH, EAST, SOUTH, WEST};

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        if (grid[y][x] == 'D') {  // Reached docking station
            std::vector<Direction> result;
            int path_length = 0;  // Initialize path length
            while (x != startX || y != startY) {
                auto dir = path[{x, y}];
                result.push_back(dir);
                x -= directions[std::distance(dirNames.begin(), std::find(dirNames.begin(), dirNames.end(), dir))].first;
                y -= directions[std::distance(dirNames.begin(), std::find(dirNames.begin(), dirNames.end(), dir))].second;
                path_length++;  // Increment path length for each step
            }
            std::reverse(result.begin(), result.end());
            return {result, path_length};  // Return both the path and its length
        }

        for (size_t i = 0; i < directions.size(); ++i) {
            int newX = x + directions[i].first;
            int newY = y + directions[i].second;
            char cellType = get(newX, newY);

            if (cellType != ' ' && cellType != 'W' && cameFrom.find({newX, newY}) == cameFrom.end()) {
                queue.push({newX, newY});
                cameFrom[{newX, newY}] = {x, y};
                path[{newX, newY}] = dirNames[i];
            }
        }
    }
    return {{}, -1};  // Return empty path and -1 if no path found
}

